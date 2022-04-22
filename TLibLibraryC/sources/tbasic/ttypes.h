#pragma once

#include <stdio.h>
#include <stdbool.h>

typedef bool TBool;

typedef FILE* TFile;
typedef int TFileDescriptor;
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

typedef char* TString;
typedef const char* const TMessage;
//typedef wchar_t* TStringW;
//typedef const wchar_t* const TMessageW;

typedef unsigned char uchar;
typedef short int hint;
typedef unsigned short int uhint;
typedef unsigned int uint;

typedef long int lint;
typedef unsigned long int ulint;
typedef long long int llint;
typedef unsigned long long int ullint;
typedef long double ldouble;
