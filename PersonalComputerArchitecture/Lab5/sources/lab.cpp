#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>

// Interface for DOS functions for MSVS/Qt/VSCode/etc.
#ifdef _WIN64
#include "../../dos.h"
#endif

// May be needed:
// void _enable(void);	-	sti
// void _disable(void);	-	cli

// Ports:
// 70h - read-only		-	RTC register code
// 71h - read and write	-	Access for |^| that register

typedef unsigned char byte_t;

/*	Registers	*/
typedef unsigned short int RTC_REGISTERS;
enum
{
	RTC_CURRENT_SECONDS = 0x00,
	RTC_ALARM_SECONDS,
	RTC_CURRENT_MINUTES,
	RTC_ALARM_MINUTES,
	RTC_CURRENT_HOURS,
	RTC_ALARM_HOURS,
	RTC_CURRENT_DAY_OF_WEEK,
	RTC_CURRENT_DAY_OF_MONTH,
	RTC_CURRENT_MONTH,
	RTC_CURRENT_YEAR,
	RTC_REGISTER_A,
	RTC_REGISTER_B,
	RTC_REGISTER_C,
	RTC_REGISTER_D,
	RTC_REGISTER_E,
};
typedef enum
{
	CLR_BIT = 0,
	SET_BIT,
	GET_BIT
} CTRL_BIT;

#define FOR_EACH_RTC_REGISTER(T_REGISTER)for (RTC_REGISTERS T_REGISTER = RTC_CURRENT_SECONDS; T_REGISTER <= RTC_REGISTER_E; ++T_REGISTER)

byte_t select_register(const RTC_REGISTERS reg)
{
	return outp(0x70, reg);
}
byte_t read_from_register(const byte_t reg)
{
	select_register(reg);
	return inp(0x71);
}
byte_t num2bit(const byte_t bit_bumber)
{
	byte_t result = 1;
	for (byte_t i = bit_bumber; i > 0; --i) result *= 2;
	return result;
}

byte_t write_to_register(const byte_t, const byte_t);

byte_t ctrl_reg_bit(const byte_t reg, const byte_t bit, const CTRL_BIT value)
{
	const byte_t temp_value = read_from_register(reg);
	switch (value)
	{
	case CLR_BIT:
		return write_to_register(reg, temp_value & (0xFF - num2bit(bit)));
	case SET_BIT:
		return write_to_register(reg, temp_value | num2bit(bit));
	case GET_BIT:
		return (temp_value & num2bit(bit)) == 0 ? CLR_BIT : SET_BIT;
	}
}
byte_t write_to_register(const byte_t reg, const byte_t reg_value)
{
	if (reg < RTC_REGISTER_A) while (ctrl_reg_bit(RTC_REGISTER_A, 7, GET_BIT) != 0) {};
	select_register(reg);
	const byte_t result = outp(0x71, reg_value);
	return result;
}

/*	Registers	*/

char* bcd2bin(byte_t bcd_byte)
{
	static char bin_value[9] = "\0\0\0\0\0\0\0\0\0";
	for (byte_t i = 0, divider = 0x80; i < 8; ++i, divider /= 2)
		bin_value[i] = (bcd_byte & divider ? '1' : '0');
	return bin_value;
}

byte_t bcd2dec(byte_t bcd_byte)
{
	return( (bcd_byte & 0x0f) + 10 * ((bcd_byte & 0xf0) >> 4) );
}
byte_t dec2bcd(byte_t dec_byte)
{
	const int temp = dec_byte / 10;
	return (temp << 4) + (dec_byte - (temp * 10));
}

void rtc_watch(void)
{
	system("cls");
	printf("Real-time clock registers:\n"
			"    Reg  bcd dec   bin:\t\t    Reg  bcd dec   bin:\n");
	FOR_EACH_RTC_REGISTER(reg)
	{
		const byte_t bcd_value = read_from_register(reg);
		printf("RTC 0%Xh: %3u %3u %s%c", reg, bcd_value, bcd2dec(bcd_value), bcd2bin(bcd_value), (reg % 2 ? '\n' : '\t'));
	}
	printf("\n");
}

void rtc_get_time(void)
{
	const byte_t day_of_week =	bcd2dec(read_from_register(RTC_CURRENT_DAY_OF_WEEK)), day_of_month = bcd2dec(read_from_register(RTC_CURRENT_DAY_OF_MONTH)),
								month = bcd2dec(read_from_register(RTC_CURRENT_MONTH)), year =	bcd2dec(read_from_register(RTC_CURRENT_YEAR)),
								hours = bcd2dec(read_from_register(RTC_CURRENT_HOURS)), minutes = bcd2dec(read_from_register(RTC_CURRENT_MINUTES)),
								seconds = bcd2dec(read_from_register(RTC_CURRENT_SECONDS));
	const char* const months[] = {
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December" };
	const char* const days_of_week[] = {
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday" };
	byte_t time_format = read_from_register(RTC_REGISTER_B) & 0x02;
	printf("\tDate:\t%s, %u %s 20%02u.\n\tTime:\t%02u:%02u:%02u, %d-hours format.\n", days_of_week[day_of_week], day_of_month, months[month-1], year,
			hours, minutes, seconds, (time_format ? 24 : 12));
}
#define get_n_check(T_MESSAGE, T_VALUE, T_LIMIT) do { printf("%s", T_MESSAGE); scanf("%u", &T_VALUE); } while (T_VALUE >= T_LIMIT)
void rtc_set_time(void)
{
	unsigned hours, minutes, seconds;
	printf("Set current time as:\n");
	get_n_check("\tHours:	 ", hours, 24u);
	get_n_check("\tMinutes: ", minutes, 60u);
	get_n_check("\tSeconds: ", seconds, 60u);
	write_to_register(RTC_CURRENT_HOURS,	dec2bcd(hours));
	write_to_register(RTC_CURRENT_MINUTES,	dec2bcd(minutes));
	write_to_register(RTC_CURRENT_SECONDS,	dec2bcd(seconds));
	rtc_get_time();
}
unsigned int general_delay_counter;
byte_t alarm_flag = 0;
// Delay interruption handler
void interrupt far new_70h_handler(...)
{
	if (ctrl_reg_bit(RTC_REGISTER_C, 6, GET_BIT) == 1)
		++general_delay_counter;
	if (ctrl_reg_bit(RTC_REGISTER_C, 5, GET_BIT) == 1)
	{
		alarm_flag = 1;
		//write_to_register(RTC_ALARM_HOURS,		0u);
		//write_to_register(RTC_ALARM_MINUTES,	0u);
		//write_to_register(RTC_ALARM_SECONDS,	0u);
		//ctrl_reg_bit(RTC_REGISTER_B, 5, CLR_BIT);
	}
	read_from_register(RTC_REGISTER_C);
	// Send signal to the controller to stop interruption
	outp(0x20, 0x20);
	outp(0xA0, 0x20);
}
void rtc_delay(const unsigned int delay_time)
{
	ctrl_reg_bit(RTC_REGISTER_B, 6, SET_BIT);
	general_delay_counter = 0;
	while (general_delay_counter < delay_time) {};
	ctrl_reg_bit(RTC_REGISTER_B, 6, CLR_BIT);
}
void rtc_set_delay(void)
{
	unsigned delay_time;
	while (1)
	{
		rtc_watch();
		printf("Enter new delay (in ms, max = 60k ms): ");
		if (!kbhit()) rtc_delay(500);
		else break;
	}
	get_n_check("", delay_time, 60000 + 1);
	ctrl_reg_bit(RTC_REGISTER_B, 6, SET_BIT);
	rtc_watch();
	rtc_delay(delay_time);
	ctrl_reg_bit(RTC_REGISTER_B, 6, CLR_BIT);
	rtc_watch();
	return;
}
void rtc_get_alarm(void)
{
	if (ctrl_reg_bit(RTC_REGISTER_B, 5, GET_BIT) == 0)
	{
		printf("Alarm was not set. Set alarm first.\n");
		return;
	}
	byte_t time_format = read_from_register(RTC_REGISTER_B) & 0x02;
	const byte_t	hours = bcd2dec(read_from_register(RTC_ALARM_HOURS)), minutes = bcd2dec(read_from_register(RTC_ALARM_MINUTES)),
					seconds = bcd2dec(read_from_register(RTC_ALARM_SECONDS));
	printf("Alarm will be triggered at %02u:%02u:%02u, %d-hours format.\n", hours, minutes, seconds, (time_format ? 24 : 12));
}
void rtc_set_alarm(void)
{
	while (1)
	{
		rtc_watch();
		printf("Alarm will be triggered at:\n\tHours:	 ");
		if (!kbhit()) sleep(1);
		else break;
	}
	unsigned hours, minutes, seconds;
	get_n_check("", hours, 24u);
	get_n_check("\tMinutes: ", minutes, 60u);
	get_n_check("\tSeconds: ", seconds, 60u);
	write_to_register(RTC_ALARM_HOURS,		dec2bcd(hours));
	write_to_register(RTC_ALARM_MINUTES,	dec2bcd(minutes));
	write_to_register(RTC_ALARM_SECONDS,	dec2bcd(seconds));
	ctrl_reg_bit(RTC_REGISTER_B, 5, SET_BIT);
	rtc_get_alarm();
}
void rtc_reset_alarm(void)
{
	write_to_register(RTC_ALARM_HOURS,		0u);
	write_to_register(RTC_ALARM_MINUTES,	0u);
	write_to_register(RTC_ALARM_SECONDS,	0u);
	ctrl_reg_bit(RTC_REGISTER_B, 5, CLR_BIT);
	printf("Alarm reset completed.\n");
}
void rtc_alarm_menu(void)
{
	char action;
	while (1)
	{
		rtc_watch();
		printf( "Real-time alarm menu:\n"
				"\tg)\tGet alarm time;\n"
				"\ts)\tSet alarm time;\n"
				"\tr)\tReset alarm time;\n"
				"\tq)\tQuit.\n");
		printf("Action: ");
		if (!kbhit())
		{
			if (alarm_flag == 1)
			{
				rtc_watch();
				printf("\n!!! [( Alarm is rining. )] !!!\n");
				alarm_flag = 0;
				system("pause");
			}
			else sleep(1);
			continue;
		}
		printf("%c\n", action = getch());
		switch (action)
		{
		case 'g':
			rtc_get_alarm();
			break;
		case 's':
			rtc_set_alarm();
			break;
		case 'r':
			rtc_reset_alarm();
			break;
		case 'q':
			return;
		case 't':
			{
				union REGS reg;
				int86(0x70,&reg,&reg);
			}
		default:
			break;
		}
		system("pause");
	}
}

// Variable for storing the old interruption handler
void interrupt (far *old_70h_handler)(...);

void control_registers(void)
{
	printf("Ctrl\t[0-E] register: ");
	printf("Ctrl\t");
	char temp;
}

int main(void)
{
	char action;
	{
		disable();
		// Save old vectors
		old_70h_handler = getvect(0x70);
		// Set new vectors (interruptions' handlers)
		setvect(0x70, new_70h_handler);
		// Allow RTC interruptions
		outp(0xA1, (inp(0xA0) & 0xFE)); // 0xFE - 1111 1110
		enable();
	}

	while (1)
	{
		rtc_watch();
		printf( "Real-time clock menu:\n"
				"\tg)\tGet RTC time;\n"
				"\ts)\tSet RTC time;\n"
				"\td)\tCall delay (in miliseconds);\n"
				"\ta)\tOpen RTC alarm menu;\n"
				"\tq)\tQuit.\n");
		printf("Action: ");
		if (!kbhit())
		{
			rtc_delay(500);
			continue;
		}
		printf("%c\n", action = getch());
		switch (action)
		{
			case 'g':
				rtc_get_time();
				break;
			case 's':
				rtc_set_time();
				break;
			case 'd':
				rtc_set_delay();
				break;
			case 'a':
				rtc_alarm_menu();
				break;
			case 'c':
				control_registers();
				break;
			case 'q':
				printf("Quitting the programm.\n");
				rtc_reset_alarm();
				{
					disable();
					// Forbid RTC interruptions
					outp(0xA1, (inp(0xA0) | 0x01)); // 0x01 - 0000 0001
					// Restore old vectors
					setvect(0x70, old_70h_handler);
					enable();
				}
				return 0;
			default:
				continue;
		}
		system("pause");
	}
}
