#pragma once

#define far
#define interrupt

void* MK_FP(int, int);
int inp(int);
void outp(int,int);

void _enable(void);
void _disable(void);
void _dos_freemem(int);
void _dos_keep(int,int);

typedef void interrupt(*vect_t)(...);
vect_t getvect(int);
void setvect(int, vect_t);

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
