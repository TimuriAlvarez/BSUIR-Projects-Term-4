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
	TBool terminate;
	size_t code;
} TException;

void handle_exception(const TException exception);

#define T_THROW_EXCEPTION(E_TYPE, E_DESCRIPTION, E_TERMINATE, E_CODE, E_HANDLER_ACTION) \
	{ \
	const TException exception = { E_TYPE, E_DESCRIPTION, { __FILE__ , __LINE__ , __func__ }, E_TERMINATE, E_CODE }; \
	handle_exception(exception); \
	E_HANDLER_ACTION \
	}
