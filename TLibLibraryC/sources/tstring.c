#include <stdarg.h>

#define T_SOURCE_FILE
#include "tstring.h"
#include "timport.h"

//	Size of allocation block (number of characters to be allocated/reallocated int the string)
static const size_t block_size = 16u;

/*	Static Const part of TString (aka TMessage)	*/
size_t T_CLASS(TString, size)(TMessage message)
{
	size_t counter = 0u;
	if (message != nullptr) while (message[counter] != '\0') ++counter;
	return counter;
}
TComparison T_CLASS(TString, compare)(TMessage message1, TMessage message2)
{
	if (message1 == message2) return kEqual;
	if (message1 == nullptr) return kLess;
	if (message2 == nullptr) return kGreater;
	const size_t size1 = T_CLASS(TString, size)(message1), size2 = T_CLASS(TString, size)(message2);
	for (size_t index = 0u; index < size1 && index < size2; ++index)
	{
		if (message1[index] > message2[index]) return kGreater;
		if (message1[index] < message2[index]) return kLess;
	}
	if (size1 > size2) return kGreater;
	if (size1 < size2) return kLess;
	return kEqual;
}
TBool T_CLASS(TString, equal)(TMessage message1, TMessage message2)
{
	return T_CLASS(TString, compare)(message1, message2) == kEqual;
}
TBool T_CLASS(TString, empty)(TMessage message)
{
	return T_CLASS(TString, size)(message) == 0u;
}
TBool T_CLASS(TString, contains)(TMessage message, const char character)
{
	for (size_t index = 0u; index < T_CLASS(TString, size)(message); ++index)
		if (message[index] == character) return true;
	return false;
}

/*	Dynamic Mutable part of TString (TString itself)	*/

T_IMPORT_MEMORY_DEFINITION(char)
T_IMPORT_MEMORY_DEFINITION(TString)

TString T_CLASS(TString, default_constructor)(void)
{
	return nullptr;
}
TString T_CLASS(TString, constructor)(TMessage format, ... )
{
	TString result = T_CLASS(TString, default_constructor)();
	size_t size, quantity;
	va_list ptr;

	va_start(ptr, format);
	size = vsnprintf(result, 0, format, ptr) + 1;
	va_end(ptr);

	for (size_t i = 0u; i < size; ++i)
		result = T_CLASS(TString, append)(result, '_');

	va_start(ptr, format);
	quantity = vsnprintf(result, size, format, ptr) + 1;
	va_end(ptr);

	if (size != quantity) T_CLASS(TConsole, print)(kDebug, "Error while constructing the string!");
	return result;
}

TString T_CLASS(TString, clear)(TString const string)
{
	return T_MEMORY_MANAGER(deallocate, char)(string);
}
TString T_CLASS(TString, destructor)(TString const string)
{
	return T_CLASS(TString, clear)(string);
}

//	Memory manager
TString T_CLASS(TString, resize)(TString const string)
{
	const size_t old_size = T_CLASS(TString, size)(string) + 1;
	return T_MEMORY_MANAGER(reallocate, char)(string, old_size, old_size + block_size);
}

TString T_CLASS(TString, append)(TString const string, const char character)
{
	TString result;
	if (T_CLASS(TString, size)(string) % block_size == 0)
		result = T_CLASS(TString, resize)(string);
	else result = string;
	result[T_CLASS(TString, size)(result)] = character;
	return result;
}
/*TString T_CLASS(TString, multy_append)(TString const string, TMessage message)
{
	TString result = string;
	for (size_t index = 0u; index < T_CLASS(TString, size)(message); ++index)
		result = T_CLASS(TString, append)(result, message[index]);
	return result;
}*/
//TString* T_CLASS(TString, chop)(TMessage string, const size_t quentity) { !chop it! }
TString T_CLASS(TString, substring)(TMessage message, const size_t index_start, const size_t index_end)
{
	TString result = nullptr;
	if (index_start <= index_end)
		for (size_t index = index_start; index <= index_end; ++index)
			result = T_CLASS(TString, append)(result, message[index]);
	else
		for (size_t index = index_end; index >= index_start; --index)
			result = T_CLASS(TString, append)(result, message[index]);
	return result;
}
TString* T_CLASS(TString, split)(TString message, TMessage splitters)
{
	size_t array_size = 0u;
	TString* result = T_MEMORY_MANAGER(allocate, TString)(array_size);
	// Extract the first token
	TString token = strtok(message, splitters);
	// loop through the string to extract all other tokens
	while(token != nullptr)
	{
		result = T_MEMORY_MANAGER(reallocate, TString)(result, array_size, array_size + 1u);
		result[array_size] = T_CLASS(TString, constructor)("%s", token);
		array_size += 1;
		token = strtok(message, splitters);
	}
	result = T_MEMORY_MANAGER(reallocate, TString)(result, array_size, array_size + 1u);
	return result;
}

void T_CLASS(TString, parser)(TString string, TMessage format, ... )
{
	__attribute__((unused)) int quantity;
	va_list ptr;

	va_start(ptr, format);
	quantity = vsscanf(string, format, ptr);
	va_end(ptr);
	/*	TODO:	'%' checking!*/
}
