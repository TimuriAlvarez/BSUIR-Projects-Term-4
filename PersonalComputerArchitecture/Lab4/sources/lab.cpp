#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>

// Interface for DOS functions for MSVS/Qt/VSCode/etc.
#ifdef _WIN64
#include "../../dos.h"
#endif

/*	Глобальные константы	*/
unsigned int notes[] = { 196, 261, 329, 196, 261, 329, 196, 261, 329 };
unsigned int note_delay = 400;

//функция установки значения счетчика
void SetCount(const int iDivider)
{
	const long int base = 1193180; //максимальная частота
	long kd;
	outp(0x43, 0xB6); //10110110 - канал 2, операция 4, режим 3, формат 0
	kd = base / iDivider;
	outp(0x42, kd % 256); // младший байт делителя
	kd /= 256;
	outp(0x42, kd); //старший байт делителя
}

//функция работы с громкоговорителем
void TurnSpeaker(const int isActive)
{
	if (isActive) outp(0x61, inp(0x61) | 3);	//устанавливаем 2 младших бита 11
	else outp(0x61, inp(0x61) & 0xFC);			//устанавливаем 2 младших бита 00
}

//функция воспроизведения песни
void PlaySound(void)
{
	for (int i = 0; i < 9; i++)
	{
		SetCount(notes[i]);
		TurnSpeaker(1);			//включаем громкоговоритель
		delay(note_delay);		//устанавливаем длительность мс
		TurnSpeaker(0);			//выключаем громкоговоритель
	}
}

//функция перевода в двоичный код
void CharToBin(unsigned char state, char* str)
{
	for (int i = 7; i >= 0; i--)
	{
		const char temp = state % 2;
		state /= 2;
		str[i] = temp + '0';
	}
	str[8] = '\0';
}
void StateAnalyrez(const char* const state)
{
	printf("\to: %c", state[0]);
	printf(" r: %s", state[1] == 1 ? "ready" : "not ready");
	printf(" t: %d", state[2]%'0' * 2 + state[3] % '0');
	printf(" m: %d", state[4]%'0' * 4 + state[5] % '0' * 2 + state[6] % '0');
	printf(" f: %s\n", state[7] == '0' ? "binary" : "BCD-codes");
}
//функция считывающая слова состояния каналов
void StateWords(void)
{
	char* bin_state;
	int iChannel;
	unsigned char state;
	bin_state = (char*)calloc(9, sizeof(char));
	if (bin_state == NULL)
	{
		printf("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	for (iChannel = 0; iChannel < 3; iChannel++)
		switch (iChannel)
		{
		case 0:
			outp(0x43, 0xE2); //заносим управляющее слово,
			//соответствующее команде RBC (Чтение состояния канала) и номеру канала 0
			state = inp(0x40); //чтение слова состояния канала 0
			CharToBin(state, bin_state);
			printf("Channel 0x40 word: %s", bin_state);
			StateAnalyrez(bin_state);
			break;
		case 1:
			bin_state[0] = '\0';
			outp(0x43, 0xE4); //заносим управляющее слово,
			//соответствующее команде RBC (Чтение состояния канала) и номеру канала 1
			state = inp(0x41); //чтение слова состояния канала 1
			CharToBin(state, bin_state);
			printf("Channel 0x41 word: %s", bin_state);
			StateAnalyrez(bin_state);
			break;
		case 2:
			bin_state[0] = '\0';
			outp(0x43, 0xE8); //заносим управляющее слово,
			//соответствующее команде RBC (Чтение состояния канала) и номеру канала 2
			state = inp(0x42); //чтение слова состояния канала 2
			CharToBin(state, bin_state);
			printf("Channel 0x42 word: %s", bin_state);
			StateAnalyrez(bin_state);
			break;
		}
	free(bin_state);
}

/*	Main menu function	*/
void main_menu(void)
{
	char choice;
	while (1)
	{
		system("cls");
		printf("p:\tPlay sound\n");
		printf("d:\tDisplay channels state words\n");
		printf("q:\tQuit\n");
		printf("\nEnter your choice: ");
		scanf("%c", &choice);
		switch (choice)
		{
			case 'p': case 'P':
				PlaySound();
			break;
			case 'd': case 'D':
				StateWords();
			break;
		case 'q': case 'Q':
			return;
		default:
			break;
		}
		system("pause");
	}
}

int main(void)
{
	main_menu();
	return 0;
}
