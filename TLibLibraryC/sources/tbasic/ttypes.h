#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <uchar.h>

typedef enum
{
	kLess = -1,
	kEqual,
	kGreater
} TComparison;
typedef enum
{
	kNormalIteration,
	kRevercedIteration
} TIterationDirection;

				//Fundamental arithmetic types:
	//Integral types:
typedef bool					TBool;
//char
typedef char16_t				char16;
typedef char32_t				char32;
typedef wchar_t					wchar;
typedef signed char				schar;
typedef short int				hint;
//int
typedef long int				lint;
typedef long long int			llint;
typedef unsigned char			uchar;
typedef unsigned short int		uhint;
typedef unsigned int			uint;
typedef unsigned long int		ulint;
typedef unsigned long long int	ullint;
	//Floating point types:
//float
//double
typedef long double				ldouble;
				//Additional types:

				//My types:
typedef uchar					byte;
typedef int						TFileDescriptor;

				//Pointers:
typedef FILE*					TFile;
typedef char*					TString;
typedef const char* const		TMessage;
typedef wchar*					TWideString;
typedef const wchar* const		TWideMessage;
