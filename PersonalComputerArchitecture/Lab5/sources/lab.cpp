#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>

// Interface for DOS functions for MSVS/Qt/VSCode/etc.
#ifdef _WIN64
#include "../../dos.h"
#endif

//void _enable(void);	-	sti
//void _disable(void);	-	cli

//Ports:
//70h & 71h

typedef char byte_t;

byte_t reg_value;
#define s_register(T_REGISTER) outp(0x70, 0x0##T_REGISTER)
#define r_register() inp(0x71)
#define sr_register(T_REGISTER) s_register(T_REGISTER); reg_value = r_register();

byte_t reg_content[8];

void byte2content(byte_t byte)
{
	
}

void rtc_condition(void)
{
	sr_register(A);
	printf("Reg 0Ah: %i\t:\n", reg_value);
	sr_register(B);
	printf("Reg 0Bh: %i\n\t:", reg_value);
	sr_register(C);
	printf("Reg 0Ch: %i\n\t:", reg_value);
	sr_register(D);
	printf("Reg 0Dh: %i\n\t:", reg_value);
	sr_register(E);
	printf("Reg 0Eh: %i\n\t:", reg_value);
}

void rtc_get(void)
{
	
}
void rtc_set(void)
{
	
}
void my_delay(void)
{
	
}
void rtc_alarm(void)
{
	
}

int main(void)
{
	while (1)
	{
		system("cls");
		rtc_condition();
		printf( "Real-time clock menu:\n"
				"\tg)\tGet RTC time;\n"
				"\ts)\tSet RTC time;\n"
				"\td)\tCall delay (in miliseconds);\n"
				"\ta)\tSet alarm;\n"
				"\tq)\tQuit.\n");
		printf("Action: ");
		const char action = getch();
		printf("%c\n", action);
		switch (action)
		{
			case 'g':
				rtc_get();
				break;
			case 's':
				rtc_set();
				break;
			case 'd':
				my_delay();
				break;
			case 'a':
				rtc_alarm();
				break;
			case 'q':
				printf("Quitting the programm.\n");
				return 0;
			default:
			printf("Invalid option! Try again.\n");
				break;
		}
		system("pause");
	}
}
