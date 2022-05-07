#pragma once

#include "../tbasic.h"

#define T_IMPORT_MATH_DECLARATION(T_MATH_TYPE) \
	T_MATH_TYPE T_FUNCTION(max, T_MATH_TYPE)(const T_MATH_TYPE a, const T_MATH_TYPE b); \
	T_MATH_TYPE T_FUNCTION(min, T_MATH_TYPE)(const T_MATH_TYPE a, const T_MATH_TYPE b); \
	T_MATH_TYPE T_FUNCTION(abs, T_MATH_TYPE)(const T_MATH_TYPE a); \
	TComparison T_FUNCTION(compare, T_MATH_TYPE)(const T_MATH_TYPE a, const T_MATH_TYPE b); \
	void T_FUNCTION(swap, T_MATH_TYPE)(T_MATH_TYPE* const a, T_MATH_TYPE* const b);

#define T_IMPORT_MATH_DEFINITION(T_MATH_TYPE) \
	T_MATH_TYPE T_FUNCTION(max, T_MATH_TYPE)(const T_MATH_TYPE a, const T_MATH_TYPE b) \
	{ \
		return a > b? a : b; \
	} \
	T_MATH_TYPE T_FUNCTION(min, T_MATH_TYPE)(const T_MATH_TYPE a, const T_MATH_TYPE b) \
	{ \
		return a < b? a : b; \
	} \
	TComparison T_FUNCTION(compare, T_MATH_TYPE)(const T_MATH_TYPE a, const T_MATH_TYPE b) \
	{ \
		if (a > b) return kGreater; \
		if (a < b) return kLess; \
		return kEqual; \
	} \
	void T_FUNCTION(swap, T_MATH_TYPE)(T_MATH_TYPE* const a, T_MATH_TYPE* const b) \
	{ \
		const T_MATH_TYPE temp = *a; \
		*a = *b; \
		*b = temp; \
	}
