#pragma once

#include "../tbasic.h"

typedef struct
{
	TMessage type;
	TMessage description;
	struct CodeLocation
	{
		TMessage file;
		size_t line;
		TMessage function;
	} code_location;
	TFlag terminate;
	size_t code;
} TException;

void handle_exception(const TException exception);

#define T_THROW_EXCEPTION(E_TYPE, E_DESCRIPTION, C_LOCATION, E_TERMINATE, E_CODE, E_RETURN) \
	{ \
	const TException exception = { E_TYPE, E_DESCRIPTION, C_LOCATION, E_TERMINATE, E_CODE }; \
	handle_exception(exception); \
	return E_RETURN; \
	}

#define E_LOCATION { __FILE__ , __LINE__ , __func__ }
