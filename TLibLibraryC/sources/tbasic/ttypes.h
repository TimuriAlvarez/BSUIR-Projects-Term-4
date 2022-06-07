#pragma once

#include <stdio.h>
#include <stddef.h>
#include <uchar.h>
#include <stdbool.h>

#include "tdeclarations.h"

typedef enum
{
	kLess = -1,
	kEqual,
	kGreater
} TComparison;

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
typedef void*                   TPointer;
typedef FILE*					TFile;

				//Strings:
typedef char*					TString;
typedef TString					T_CONTAINER(TString, char, T_CONTAINER_POSTFIX);
typedef const char* const		TMessage;
typedef TMessage				T_CONTAINER(TMessage, char, T_CONTAINER_POSTFIX);
typedef wchar*					TWideString;
typedef TWideString				T_CONTAINER(TString, wchar, T_CONTAINER_POSTFIX);
typedef const wchar* const		TWideMessage;
typedef TWideMessage			T_CONTAINER(TMessage, wchar, T_CONTAINER_POSTFIX);
