#pragma once

#include <stdint.h>
#include <float.h>
#include <math.h>
#include <limits.h>

#include "tnumeric.h"

#define T_TYPE TBool

#define T_NUMERIC_TABLE_DEFINITION_PART_1(T_TYPE,T_SPC,T_SGN,T_UNS,T_INT,T_XCT,T_INF,T_QNN,T_SNN,T_DNR,T_IEC,T_BND,T_MDL,T_TRP,T_TNN) \
	TBool				T_CONTAINER(TNumeric, T_TYPE, is_specialized)(void)		{ return T_SPC; } \
	TBool				T_CONTAINER(TNumeric, T_TYPE, is_signed)(void)			{ return T_SGN; } \
	TBool				T_CONTAINER(TNumeric, T_TYPE, is_unsigned)(void)		{ return T_UNS; } \
	TBool				T_CONTAINER(TNumeric, T_TYPE, is_integer)(void)			{ return T_INT; } \
	TBool				T_CONTAINER(TNumeric, T_TYPE, is_exact)(void)			{ return T_XCT; } \
	TBool				T_CONTAINER(TNumeric, T_TYPE, has_infinity)(void)		{ return T_INF; } \
	TBool				T_CONTAINER(TNumeric, T_TYPE, has_quiet_NaN)(void)		{ return T_QNN; } \
	TBool				T_CONTAINER(TNumeric, T_TYPE, has_signaling_NaN)(void)	{ return T_SNN; } \
	TBool				T_CONTAINER(TNumeric, T_TYPE, has_denorm_loss)(void)	{ return T_DNR; } \
	TBool				T_CONTAINER(TNumeric, T_TYPE, is_iec559)(void)			{ return T_IEC; } \
	TBool				T_CONTAINER(TNumeric, T_TYPE, is_bounded)(void)			{ return T_BND; } \
	TBool				T_CONTAINER(TNumeric, T_TYPE, is_modulo)(void)			{ return T_MDL; } \
	TBool				T_CONTAINER(TNumeric, T_TYPE, traps)(void)				{ return T_TRP; } \
	TBool				T_CONTAINER(TNumeric, T_TYPE, tinyness_before)(void)	{ return T_TNN; }

#define T_NUMERIC_TABLE_DEFINITION_PART_2(T_TYPE,T_DNR,T_RND) \
	float_denorm_style	T_CONTAINER(TNumeric, T_TYPE, has_denorm)(void)			{ return T_DNR; } \
	float_round_style	T_CONTAINER(TNumeric, T_TYPE, round_style)(void)		{ return T_RND; }

#define T_NUMERIC_TABLE_DEFINITION_PART_3(T_TYPE,T_DIGT,T_DT10,T_MD10,T_RADX,T_mEXP,T_mE10,T_MEXP,T_ME10) \
	int					T_CONTAINER(TNumeric, T_TYPE, digits)(void)				{ return T_DIGT; } \
	int					T_CONTAINER(TNumeric, T_TYPE, digits10)(void)			{ return T_DT10; } \
	int					T_CONTAINER(TNumeric, T_TYPE, max_digits10)(void)		{ return T_MD10; } \
	int					T_CONTAINER(TNumeric, T_TYPE, radix)(void)				{ return T_RADX; } \
	int					T_CONTAINER(TNumeric, T_TYPE, min_exponent)(void)		{ return T_mEXP; } \
	int					T_CONTAINER(TNumeric, T_TYPE, min_exponent10)(void)		{ return T_mE10; } \
	int					T_CONTAINER(TNumeric, T_TYPE, max_exponent)(void)		{ return T_MEXP; } \
	int					T_CONTAINER(TNumeric, T_TYPE, max_exponent10)(void)		{ return T_ME10; }

#define T_NUMERIC_TABLE_DEFINITION_PART_4(T_TYPE,T_MIN,T_MAX,T_LOW) \
	T_TYPE				T_CONTAINER(TNumeric, T_TYPE, min)(void)				{ return T_MIN; } \
	T_TYPE				T_CONTAINER(TNumeric, T_TYPE, max)(void)				{ return T_MAX; } \
	T_TYPE				T_CONTAINER(TNumeric, T_TYPE, lowest)(void)				{ return T_LOW; }

#define T_NUMERIC_TABLE_DEFINITION_PART_5(T_TYPE,T_EPS,R_RND,T_INF,T_QNN,T_SNN,T_DNR) \
	T_TYPE				T_CONTAINER(TNumeric, T_TYPE, epsilon)(void)			{ return T_EPS; } \
	T_TYPE				T_CONTAINER(TNumeric, T_TYPE, round_error)(void)		{ return R_RND; } \
	T_TYPE				T_CONTAINER(TNumeric, T_TYPE, infinity)(void)			{ return T_INF; } \
	T_TYPE				T_CONTAINER(TNumeric, T_TYPE, quiet_NaN)(void)			{ return T_QNN; } \
	T_TYPE				T_CONTAINER(TNumeric, T_TYPE, signaling_NaN)(void)		{ return T_SNN; } \
	T_TYPE				T_CONTAINER(TNumeric, T_TYPE, denorm_min)(void)			{ return T_DNR; }

				//Fundamental arithmetic types:
	//Integral types:
T_NUMERIC_TABLE_DEFINITION_PART_1(  TBool,	true,	false,	 true,	true,	true,	false,	false,	false,	false,	false,	true,	false,	true,	false) //0
T_NUMERIC_TABLE_DEFINITION_PART_1(   char,	true,	 true,	false,	true,	true,	false,	false,	false,	false,	false,	true,	false,	true,	false) //1
T_NUMERIC_TABLE_DEFINITION_PART_1( char16,	true,	false,	 true,	true,	true,	false,	false,	false,	false,	false,	true,	 true,	true,	false) //2
T_NUMERIC_TABLE_DEFINITION_PART_1( char32,	true,	false,	 true,	true,	true,	false,	false,	false,	false,	false,	true,	 true,	true,	false) //2
T_NUMERIC_TABLE_DEFINITION_PART_1(  wchar,	true,	false,	 true,	true,	true,	false,	false,	false,	false,	false,	true,	 true,	true,	false) //2
T_NUMERIC_TABLE_DEFINITION_PART_1(  schar,	true,	 true,	false,	true,	true,	false,	false,	false,	false,	false,	true,	false,	true,	false) //1
T_NUMERIC_TABLE_DEFINITION_PART_1(   hint,	true,	 true,	false,	true,	true,	false,	false,	false,	false,	false,	true,	false,	true,	false) //1
T_NUMERIC_TABLE_DEFINITION_PART_1(	int,	true,	 true,	false,	true,	true,	false,	false,	false,	false,	false,	true,	false,	true,	false) //1
T_NUMERIC_TABLE_DEFINITION_PART_1(   lint,	true,	 true,	false,	true,	true,	false,	false,	false,	false,	false,	true,	false,	true,	false) //1
T_NUMERIC_TABLE_DEFINITION_PART_1(  llint,	true,	 true,	false,	true,	true,	false,	false,	false,	false,	false,	true,	false,	true,	false) //1
T_NUMERIC_TABLE_DEFINITION_PART_1(  uchar,	true,	false,	 true,	true,	true,	false,	false,	false,	false,	false,	true,	 true,	true,	false) //2
T_NUMERIC_TABLE_DEFINITION_PART_1(  uhint,	true,	false,	 true,	true,	true,	false,	false,	false,	false,	false,	true,	 true,	true,	false) //2
T_NUMERIC_TABLE_DEFINITION_PART_1(   uint,	true,	false,	 true,	true,	true,	false,	false,	false,	false,	false,	true,	 true,	true,	false) //2
T_NUMERIC_TABLE_DEFINITION_PART_1(  ulint,	true,	false,	 true,	true,	true,	false,	false,	false,	false,	false,	true,	 true,	true,	false) //2
T_NUMERIC_TABLE_DEFINITION_PART_1( ullint,	true,	false,	 true,	true,	true,	false,	false,	false,	false,	false,	true,	 true,	true,	false) //2
	//Floating point types:
T_NUMERIC_TABLE_DEFINITION_PART_1(  float,	true,	true,	false,	false,	false,	 true,	 true,	 true,	false,	 true,	 true,	false,	false,	false) //3
T_NUMERIC_TABLE_DEFINITION_PART_1( double,	true,	true,	false,	false,	false,	 true,	 true,	 true,	false,	 true,	 true,	false,	false,	false) //3
T_NUMERIC_TABLE_DEFINITION_PART_1(ldouble,	true,	true,	false,	false,	false,	 true,	 true,	 true,	false,	 true,	 true,	false,	false,	false) //3

				//Fundamental arithmetic types:
	//Integral types:
T_NUMERIC_TABLE_DEFINITION_PART_2(  TBool,	 denorm_absent,		round_toward_zero)
T_NUMERIC_TABLE_DEFINITION_PART_2(   char,	 denorm_absent,		round_toward_zero)
T_NUMERIC_TABLE_DEFINITION_PART_2( char16,	 denorm_absent,		round_toward_zero)
T_NUMERIC_TABLE_DEFINITION_PART_2( char32,	 denorm_absent,		round_toward_zero)
T_NUMERIC_TABLE_DEFINITION_PART_2(  wchar,	 denorm_absent,		round_toward_zero)
T_NUMERIC_TABLE_DEFINITION_PART_2(  schar,	 denorm_absent,		round_toward_zero)
T_NUMERIC_TABLE_DEFINITION_PART_2(   hint,	 denorm_absent,		round_toward_zero)
T_NUMERIC_TABLE_DEFINITION_PART_2(	int,	 denorm_absent,		round_toward_zero)
T_NUMERIC_TABLE_DEFINITION_PART_2(   lint,	 denorm_absent,		round_toward_zero)
T_NUMERIC_TABLE_DEFINITION_PART_2(  llint,	 denorm_absent,		round_toward_zero)
T_NUMERIC_TABLE_DEFINITION_PART_2(  uchar,	 denorm_absent,		round_toward_zero)
T_NUMERIC_TABLE_DEFINITION_PART_2(  uhint,	 denorm_absent,		round_toward_zero)
T_NUMERIC_TABLE_DEFINITION_PART_2(   uint,	 denorm_absent,		round_toward_zero)
T_NUMERIC_TABLE_DEFINITION_PART_2(  ulint,	 denorm_absent,		round_toward_zero)
T_NUMERIC_TABLE_DEFINITION_PART_2( ullint,	 denorm_absent,		round_toward_zero)
	//Floating point types:
T_NUMERIC_TABLE_DEFINITION_PART_2(  float,	denorm_present,		 round_to_nearest)
T_NUMERIC_TABLE_DEFINITION_PART_2( double,	denorm_present,		 round_to_nearest)
T_NUMERIC_TABLE_DEFINITION_PART_2(ldouble,	denorm_present,		 round_to_nearest)

				//Fundamental arithmetic types:
	//Integral types:
T_NUMERIC_TABLE_DEFINITION_PART_3(  TBool,			1/**/,	   0/**/,		 0,			2,			   0,				  0,			   0,				  0)
T_NUMERIC_TABLE_DEFINITION_PART_3(   char,			7/**/,	   2/**/,		 0,			2,			   0,				  0,			   0,				  0)
T_NUMERIC_TABLE_DEFINITION_PART_3( char16,		   16/**/,	   4/**/,		 0,			2,			   0,				  0,			   0,				  0)
T_NUMERIC_TABLE_DEFINITION_PART_3( char32,		   32/**/,	   9/**/,		 0,			2,			   0,				  0,			   0,				  0)
T_NUMERIC_TABLE_DEFINITION_PART_3(  wchar,		   16/**/,	   4/**/,		 0,			2,			   0,				  0,			   0,				  0)
T_NUMERIC_TABLE_DEFINITION_PART_3(  schar,			7/**/,	   2/**/,		 0,			2,			   0,				  0,			   0,				  0)
T_NUMERIC_TABLE_DEFINITION_PART_3(   hint,		   15/**/,	   4/**/,		 0,			2,			   0,				  0,			   0,				  0)
T_NUMERIC_TABLE_DEFINITION_PART_3(	int,		   31/**/,	   9/**/,		 0,			2,			   0,				  0,			   0,				  0)
T_NUMERIC_TABLE_DEFINITION_PART_3(   lint,		   31/**/,	   9/**/,		 0,			2,			   0,				  0,			   0,				  0)
T_NUMERIC_TABLE_DEFINITION_PART_3(  llint,		   63/**/,	  18/**/,		 0,			2,			   0,				  0,			   0,				  0)
T_NUMERIC_TABLE_DEFINITION_PART_3(  uchar,			8/**/,	   2/**/,		 0,			2,			   0,				  0,			   0,				  0)
T_NUMERIC_TABLE_DEFINITION_PART_3(  uhint,		   16/**/,	   4/**/,		 0,			2,			   0,				  0,			   0,				  0)
T_NUMERIC_TABLE_DEFINITION_PART_3(   uint,		   32/**/,	   9/**/,		 0,			2,			   0,				  0,			   0,				  0)
T_NUMERIC_TABLE_DEFINITION_PART_3(  ulint,		   32/**/,	   9/**/,		 0,			2,			   0,				  0,			   0,				  0)
T_NUMERIC_TABLE_DEFINITION_PART_3( ullint,		   64/**/,	  19/**/,		 0,			2,			   0,				  0,			   0,				  0)
	//Floating point types:
T_NUMERIC_TABLE_DEFINITION_PART_3(  float,	 FLT_MANT_DIG,	 FLT_DIG,	 9/**/,	FLT_RADIX,	 FLT_MIN_EXP,	 FLT_MIN_10_EXP,	 FLT_MAX_EXP,	 FLT_MAX_10_EXP)
T_NUMERIC_TABLE_DEFINITION_PART_3( double,	 DBL_MANT_DIG,	 DBL_DIG,	17/**/,	FLT_RADIX,	 DBL_MIN_EXP,	 DBL_MIN_10_EXP,	 DBL_MAX_EXP,	 DBL_MAX_10_EXP)
T_NUMERIC_TABLE_DEFINITION_PART_3(ldouble,	LDBL_MANT_DIG,	LDBL_DIG,	21/**/,	FLT_RADIX,	LDBL_MIN_EXP,	LDBL_MIN_10_EXP,	LDBL_MAX_EXP,	LDBL_MAX_10_EXP)

				//Fundamental arithmetic types:
	//Integral types:
T_NUMERIC_TABLE_DEFINITION_PART_4(  TBool,								  false,								   true,		   T_CONTAINER(TNumeric, TBool, min)())
T_NUMERIC_TABLE_DEFINITION_PART_4(   char,							   CHAR_MIN,							   CHAR_MAX,			T_CONTAINER(TNumeric, char, min)())
T_NUMERIC_TABLE_DEFINITION_PART_4( char16,	T_CONTAINER(TNumeric, uhint, min)(),	T_CONTAINER(TNumeric, uhint, max)(),		  T_CONTAINER(TNumeric, char16, min)())
T_NUMERIC_TABLE_DEFINITION_PART_4( char32,	 T_CONTAINER(TNumeric, uint, min)(),	 T_CONTAINER(TNumeric, uint, max)(),		  T_CONTAINER(TNumeric, char32, min)())
T_NUMERIC_TABLE_DEFINITION_PART_4(  wchar,	T_CONTAINER(TNumeric, uhint, min)(),	T_CONTAINER(TNumeric, uhint, max)(),		   T_CONTAINER(TNumeric, wchar, min)())
T_NUMERIC_TABLE_DEFINITION_PART_4(  schar,							  SCHAR_MIN,							  SCHAR_MAX,		   T_CONTAINER(TNumeric, schar, min)())
T_NUMERIC_TABLE_DEFINITION_PART_4(   hint,							   SHRT_MIN,							   SHRT_MAX,			T_CONTAINER(TNumeric, hint, min)())
T_NUMERIC_TABLE_DEFINITION_PART_4(	int,							    INT_MIN,								INT_MAX,			 T_CONTAINER(TNumeric, int, min)())
T_NUMERIC_TABLE_DEFINITION_PART_4(   lint,							   LONG_MIN,							   LONG_MAX,			T_CONTAINER(TNumeric, lint, min)())
T_NUMERIC_TABLE_DEFINITION_PART_4(  llint,							  LLONG_MIN,							  LLONG_MAX,		   T_CONTAINER(TNumeric, llint, min)())
T_NUMERIC_TABLE_DEFINITION_PART_4(  uchar,									 0u,							  UCHAR_MAX,		   T_CONTAINER(TNumeric, uchar, min)())
T_NUMERIC_TABLE_DEFINITION_PART_4(  uhint,									 0u,							   SHRT_MAX,		   T_CONTAINER(TNumeric, uhint, min)())
T_NUMERIC_TABLE_DEFINITION_PART_4(   uint,									 0u,							   UINT_MAX,			T_CONTAINER(TNumeric, uint, min)())
T_NUMERIC_TABLE_DEFINITION_PART_4(  ulint,									0lu,							  ULONG_MAX,		   T_CONTAINER(TNumeric, ulint, min)())
T_NUMERIC_TABLE_DEFINITION_PART_4( ullint,									0Lu,							 ULLONG_MAX,		  T_CONTAINER(TNumeric, ullint, min)())
	//Floating point types:
T_NUMERIC_TABLE_DEFINITION_PART_4(  float,								FLT_MIN,								FLT_MAX,	  (-1*T_CONTAINER(TNumeric, float, max)()))
T_NUMERIC_TABLE_DEFINITION_PART_4( double,								DBL_MIN,								DBL_MAX,	 (-1*T_CONTAINER(TNumeric, double, max)()))
T_NUMERIC_TABLE_DEFINITION_PART_4(ldouble,							   LDBL_MIN,							   LDBL_MAX,	(-1*T_CONTAINER(TNumeric, ldouble, max)()))

				//Fundamental arithmetic types:
	//Integral types:
T_NUMERIC_TABLE_DEFINITION_PART_5(  TBool,		   false,		  false,	   false,	false,	false,		 T_CONTAINER(TNumeric, TBool, min)()) //0
T_NUMERIC_TABLE_DEFINITION_PART_5(   char,			   0,			  0,		   0,		0,		0,		  T_CONTAINER(TNumeric, char, min)()) //0
T_NUMERIC_TABLE_DEFINITION_PART_5( char16,			   0,			  0,		   0,		0,		0,		T_CONTAINER(TNumeric, char16, min)()) //0
T_NUMERIC_TABLE_DEFINITION_PART_5( char32,			   0,			  0,		   0,		0,		0,		T_CONTAINER(TNumeric, char32, min)()) //0
T_NUMERIC_TABLE_DEFINITION_PART_5(  wchar,			   0,			  0,		   0,		0,		0,		 T_CONTAINER(TNumeric, wchar, min)()) //0
T_NUMERIC_TABLE_DEFINITION_PART_5(  schar,			   0,			  0,		   0,		0,		0,		 T_CONTAINER(TNumeric, schar, min)()) //0
T_NUMERIC_TABLE_DEFINITION_PART_5(   hint,			   0,			  0,		   0,		0,		0,		  T_CONTAINER(TNumeric, hint, min)()) //0
T_NUMERIC_TABLE_DEFINITION_PART_5(    int,			   0,			  0,		   0,		0,		0,		   T_CONTAINER(TNumeric, int, min)()) //0
T_NUMERIC_TABLE_DEFINITION_PART_5(   lint,			   0,			  0,		   0,		0,		0,		  T_CONTAINER(TNumeric, lint, min)()) //0
T_NUMERIC_TABLE_DEFINITION_PART_5(  llint,			   0,			  0,		   0,		0,		0,		 T_CONTAINER(TNumeric, llint, min)()) //0
T_NUMERIC_TABLE_DEFINITION_PART_5(  uchar,			   0,			  0,		   0,		0,		0,		 T_CONTAINER(TNumeric, uchar, min)()) //0
T_NUMERIC_TABLE_DEFINITION_PART_5(  uhint,			   0,			  0,		   0,		0,		0,		 T_CONTAINER(TNumeric, uhint, min)()) //0
T_NUMERIC_TABLE_DEFINITION_PART_5(   uint,			   0,			  0,		   0,		0,		0,		  T_CONTAINER(TNumeric, uint, min)()) //0
T_NUMERIC_TABLE_DEFINITION_PART_5(  ulint,			   0,			  0,		   0,		0,		0,		 T_CONTAINER(TNumeric, ulint, min)()) //0
T_NUMERIC_TABLE_DEFINITION_PART_5( ullint,			   0,			  0,		   0,		0,		0,		T_CONTAINER(TNumeric, ullint, min)()) //0
	//Floating point types:
T_NUMERIC_TABLE_DEFINITION_PART_5(  float,	 FLT_EPSILON,		0.5/**/,	INFINITY,	  NAN,	  NAN,								FLT_TRUE_MIN) //1
T_NUMERIC_TABLE_DEFINITION_PART_5( double,	 DBL_EPSILON,	   0.5l/**/,	INFINITY,	  NAN,	  NAN,								DBL_TRUE_MIN) //1
T_NUMERIC_TABLE_DEFINITION_PART_5(ldouble,	LDBL_EPSILON,	   0.5L/**/,	INFINITY,	  NAN,	  NAN,							   LDBL_TRUE_MIN) //1

#undef T_NUMERIC_TABLE_DEFINITION_PART_1
#undef T_NUMERIC_TABLE_DEFINITION_PART_2
#undef T_NUMERIC_TABLE_DEFINITION_PART_3
#undef T_NUMERIC_TABLE_DEFINITION_PART_4
#undef T_NUMERIC_TABLE_DEFINITION_PART_5
