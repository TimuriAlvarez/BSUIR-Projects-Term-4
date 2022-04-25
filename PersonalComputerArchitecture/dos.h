#pragma once

#define far
#define interrupt

void* MK_FP(int, int);
int inp(int);
int outp(int,int);

void enable(void);
void disable(void);
void dos_freemem(int);
void dos_keep(int,int);

void _enable(void);
void _disable(void);
void _dos_freemem(int);
void _dos_keep(int,int);

typedef void interrupt(*vect_t)(...);
vect_t getvect(int);
void setvect(int, vect_t);

#define _interrupt
#define _far
typedef void _interrupt (_far *vect_t_2)(...);
vect_t_2 _dos_getvect(int);
void _dos_setvect(int, vect_t_2);

unsigned* _psp = 0;

enum Segments
{
	_DS,
	_CS,
	_SP,
};

unsigned temp_offset;

#define FP_SEG(p)  p
#define FP_OFF(p)  p+=temp_offset

void delay(int);

#define T_REGISTER(LETTER) unsigned LETTER##x, LETTER##h, LETTER##l
union REGS
{
	struct
	{
		T_REGISTER(a);
		T_REGISTER(b);
		T_REGISTER(c);
		T_REGISTER(d), cflag;
	} h,x;
};
#undef T_REGISTER
void int86(int,union REGS*,union REGS*);

void sleep(unsigned int);
