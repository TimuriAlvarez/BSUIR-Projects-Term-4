#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>

// Interface for DOS functions for MSVS/Qt/VSCode/etc.
#ifdef _WIN64
#include "../../dos.h"
#endif

typedef struct _SYSTIMER_
{
	char hour;						 // часы
	char min;							// минуты
	char sec;							// секунды
	unsigned year;				 // год
	char month;						// месяц
	char day;							// число
	char daylight_savings; // флаг летнего времени
} SYSTIMER;

#define RTC_GET_TIME		 2 // прочитать показания часов;
#define RTC_SET_TIME		 3 // установить часы;
#define RTC_GET_DATE		 4 // прочитать дату;
#define RTC_SET_DATE		 5 // установить дату;
#define RTC_SET_ALARM		6 // установить будильник;
#define RTC_CLEAR_ALARM	7 // сбросить будильник.

int bcd1bin(char *bcd);
int bcd2bin(char *bcd);
void bin1bcd(int bin, char *bcd);
void _interrupt _far alarm(void);
int timer(char fn, SYSTIMER *tm);

// Выключаем проверку стека и указателей
#pragma check_stack( off )
#pragma check_pointer( off )

// Макро для выдачи звукового сигнала

#define BEEP _asm { \
	_asm mov bx,0 \
	_asm mov ax, 0E07h \
	_asm int 10h }

// Отменим макрос BEEP
#undef BEEP
#define BEEP /*	Тут был бип.	*/


// Прототип программы-обработчика прерывания
// будильника
void _interrupt _far alarm(void);

// Переменная для хранения старого
// вектора будильника
void (_interrupt _far *old_4a)(void);

union REGS reg;

int main(void)
{
	const char *month_to_text[] =
	{
	"январь",
	"февраль",
	"март",
	"апрель",
	"май",
	"июнь",
	"июль",
	"август",
	"сентябрь",
	"октябрь",
	"ноябрь",
	"декабрь"
	};

	SYSTIMER tmr;

	// Определяем текущие дату и время
	timer(RTC_GET_DATE, &tmr);
	timer(RTC_GET_TIME, &tmr);

	// Выводим дату и время на экран
	printf("\nСейчас %d год, %s, %d число."
	"\n",
	bcd2bin((char*)&(tmr.year)),
	month_to_text[bcd1bin(&(tmr.month)) - 1],
	bcd1bin(&(tmr.day)));

	printf("\nВремя - %02.2d:%02.2d:%02.2d"
	"\n",
	bcd1bin(&(tmr.hour)),
	bcd1bin(&(tmr.min)),
	bcd1bin(&(tmr.sec)));

	// Для установки будильника увеличиваем
	// счетчик минут на единицу. Для упрощения
	// программы мы не проверяем счетчик на
	// переполнение, поэтому если текущее
	// значение счетчика минут равно 59,
	// будильник не сработает. Вы можете сами
	// немного усовершенствовать программу для
	// проверки переполнения
	bin1bcd(bcd1bin(&(tmr.min)) + 1, &(tmr.min));

	// Выводим на экран время, когда сработает
	// будильник.
	printf("\nВремя срабатывания будильника"
	"- %02.2d:%02.2d:%02.2d"
	"\n",
	bcd1bin(&(tmr.hour)),
	bcd1bin(&(tmr.min)),
	bcd1bin(&(tmr.sec)));

	// Подключаем свой обработчик прерывания
	// будильника, старое значение вектора
	// 0x4a сохраняем
	old_4a = _dos_getvect(0x4a);

	_dos_setvect(0x4a, alarm);

	// Устанавливаем будильник
	timer(RTC_SET_ALARM, &tmr);

	printf("\nБудильник установлен. Для отмены "
	"и завершения программы нажмите"
	"\nлюбую клавишу...");

	getch();

	// Сбрасываем будильник и восстанавливаем
	// вектор прерывания будильника
	timer(RTC_CLEAR_ALARM, &tmr);

	_dos_setvect(0x4a, old_4a);

	return 0;
}

// ----------------------------------
// Преобразование однобайтового
// числа из формата BCD в двоичный
// формат
// ----------------------------------
int bcd1bin(char *bcd)
{
	return( (*bcd & 0x0f) + 10 * ((*bcd & 0xf0) >> 4) );
}

// ----------------------------------
// Преобразование двухбайтового
// числа из формата BCD в двоичный
// формат
// ----------------------------------
int bcd2bin(char *bcd)
{
	return( bcd1bin(bcd) +
	100 * bcd1bin(bcd + 1) );
}

// ----------------------------------
// Преобразование однобайтового
// числа из двоичного формата
// формат BCD
// ----------------------------------
void bin1bcd(int bin, char *bcd)
{
	int i;
	i = bin / 10;
	*bcd = (i << 4) + (bin - (i * 10));
}

// ----------------------------------
// Программа получает управление
// при срабатывании будильника.
// Ее назначение - выдать звуковой сигнал
// ----------------------------------
void _interrupt _far alarm(void)
{
	BEEP;
	BEEP;
	BEEP;
	BEEP;
	BEEP;
	BEEP;
	BEEP;
}

/**
*.Name				 timer
*.Title				Работа с часами реального времени
*
*.Descr				Эта функция предназначена для обслуживания
*							системных часов реального времени через
*							прерывание INT 1Ah
*
*.Proto				int timer(char fn, SYSTIMER *tm)
*
*.Params			 char		 fn - выполняемая функция:
*
*							RTC_GET_TIME			- прочитать показания часов;
*							RTC_SET_TIME			- установить часы;
*							RTC_GET_DATE			- прочитать дату;
*							RTC_SET_DATE			- установить дату;
*							RTC_SET_ALARM		 - установить будильник;
*							RTC_CLEAR_ALARM	 - сбросить будильник.
*
*							SYSTIMER tm - структура, содержащая данные
*														для установки часов или
*														показания часов:
*
*.Return			 0	 - успешное выполнение функции;
*							-1	- часы реального времени отсутствуют
*										в компьютере;
**/
int timer(char fn, SYSTIMER *tm)
{
	reg.h.ah = fn;

	switch (fn)
	{
	case RTC_SET_TIME:
	{
		reg.h.ch = tm->hour;
		reg.h.cl = tm->min;
		reg.h.dh = tm->sec;
		reg.h.dl = tm->daylight_savings;
		break;
	}

	case RTC_SET_DATE:
	{
		reg.x.cx = tm->year;
		reg.h.dh = tm->month;
		reg.h.dl = tm->day;
		break;
	}

	case RTC_SET_ALARM:
	{
		reg.h.ch = tm->hour;
		reg.h.cl = tm->min;
		reg.h.dh = tm->sec;
		break;
	}
	}

	int86(0x1a,&reg,&reg);

	if(reg.x.cflag == 1)
	return(-1);

	switch (fn)
	{
	case RTC_GET_TIME:
	{
		tm->hour = reg.h.ch;
		tm->min = reg.h.cl;
		tm->sec = reg.h.dh;
		break;
	}

	case RTC_GET_DATE:
	{
		tm->year = reg.x.cx;
		tm->month = reg.h.dh;
		tm->day = reg.h.dl;
		break;
	}
	}
	return 0;
}
