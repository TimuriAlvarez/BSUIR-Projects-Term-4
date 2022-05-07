#pragma once

#include "../tbasic.h"

typedef enum
{
	denorm_indeterminate		= -1,
	denorm_absent				=  0,
	denorm_present				=  1,
} float_denorm_style;
typedef enum
{
	round_indeterminate			= -1,
	round_toward_zero			=  0,
	round_to_nearest			=  1,
	round_toward_infinity		=  2,
	round_toward_neg_infinity	=  3,
} float_round_style;

#define T_NUMERIC_TABLE_DECLARATION(T_TYPE) \
	TBool				T_CONTAINER(TNumeric, T_TYPE, is_specialized)(void); \
	TBool				T_CONTAINER(TNumeric, T_TYPE, is_signed)(void); \
	TBool				T_CONTAINER(TNumeric, T_TYPE, is_unsigned)(void); \
	TBool				T_CONTAINER(TNumeric, T_TYPE, is_integer)(void); \
	TBool				T_CONTAINER(TNumeric, T_TYPE, is_exact)(void); \
	TBool				T_CONTAINER(TNumeric, T_TYPE, has_infinity)(void); \
	TBool				T_CONTAINER(TNumeric, T_TYPE, has_quiet_NaN)(void); \
	TBool				T_CONTAINER(TNumeric, T_TYPE, has_signaling_NaN)(void); \
	TBool				T_CONTAINER(TNumeric, T_TYPE, has_denorm_loss)(void); \
	TBool				T_CONTAINER(TNumeric, T_TYPE, is_iec559)(void); \
	TBool				T_CONTAINER(TNumeric, T_TYPE, is_bounded)(void); \
	TBool				T_CONTAINER(TNumeric, T_TYPE, is_modulo)(void); \
	TBool				T_CONTAINER(TNumeric, T_TYPE, traps)(void); \
	TBool				T_CONTAINER(TNumeric, T_TYPE, tinyness_before)(void); \
	float_denorm_style	T_CONTAINER(TNumeric, T_TYPE, has_denorm)(void); \
	float_round_style	T_CONTAINER(TNumeric, T_TYPE, round_style)(void); \
	int					T_CONTAINER(TNumeric, T_TYPE, digits)(void); \
	int					T_CONTAINER(TNumeric, T_TYPE, digits10)(void); \
	int					T_CONTAINER(TNumeric, T_TYPE, max_digits10)(void); \
	int					T_CONTAINER(TNumeric, T_TYPE, radix)(void); \
	int					T_CONTAINER(TNumeric, T_TYPE, min_exponent)(void); \
	int					T_CONTAINER(TNumeric, T_TYPE, min_exponent10)(void); \
	int					T_CONTAINER(TNumeric, T_TYPE, max_exponent)(void); \
	int					T_CONTAINER(TNumeric, T_TYPE, max_exponent10)(void); \
	T_TYPE				T_CONTAINER(TNumeric, T_TYPE, min)(void); \
	T_TYPE				T_CONTAINER(TNumeric, T_TYPE, max)(void); \
	T_TYPE				T_CONTAINER(TNumeric, T_TYPE, lowest)(void); \
	T_TYPE				T_CONTAINER(TNumeric, T_TYPE, epsilon)(void); \
	T_TYPE				T_CONTAINER(TNumeric, T_TYPE, round_error)(void); \
	T_TYPE				T_CONTAINER(TNumeric, T_TYPE, infinity)(void); \
	T_TYPE				T_CONTAINER(TNumeric, T_TYPE, quiet_NaN)(void); \
	T_TYPE				T_CONTAINER(TNumeric, T_TYPE, signaling_NaN)(void); \
	T_TYPE				T_CONTAINER(TNumeric, T_TYPE, denorm_min)(void);

				//Fundamental arithmetic types:
	//Integral types:
T_NUMERIC_TABLE_DECLARATION(TBool)
T_NUMERIC_TABLE_DECLARATION(char)
T_NUMERIC_TABLE_DECLARATION(char16)
T_NUMERIC_TABLE_DECLARATION(char32)
T_NUMERIC_TABLE_DECLARATION(wchar)
T_NUMERIC_TABLE_DECLARATION(schar)
T_NUMERIC_TABLE_DECLARATION(hint)
T_NUMERIC_TABLE_DECLARATION(int)
T_NUMERIC_TABLE_DECLARATION(lint)
T_NUMERIC_TABLE_DECLARATION(llint)
T_NUMERIC_TABLE_DECLARATION(uchar)
T_NUMERIC_TABLE_DECLARATION(uhint)
T_NUMERIC_TABLE_DECLARATION(uint)
T_NUMERIC_TABLE_DECLARATION(ulint)
T_NUMERIC_TABLE_DECLARATION(ullint)
	//Floating point types:
T_NUMERIC_TABLE_DECLARATION(float)
T_NUMERIC_TABLE_DECLARATION(double)
T_NUMERIC_TABLE_DECLARATION(ldouble)
	//My types:
T_NUMERIC_TABLE_DECLARATION(TPointer)

#undef T_NUMERIC_TABLE_DECLARATION
