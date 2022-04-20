#include <string.h>

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
TFlag T_CLASS(TString, equal)(TMessage message1, TMessage message2)
{
	return T_CLASS(TString, compare)(message1, message2) == kEqual;
}
TFlag T_CLASS(TString, empty)(TMessage message)
{
	return T_CLASS(TString, size)(message) == 0u;
}
TFlag T_CLASS(TString, contains)(TMessage message, const char character)
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
TString T_CLASS(TString, constructor)(TMessage message)
{
	return T_CLASS(TString, multy_append)(nullptr, message);
}
TString T_CLASS(TString, clear)(TString const string)
{
	return T_FUNCTION(delete, char)(string);
}
TString T_CLASS(TString, destructor)(TString const string)
{
	return T_CLASS(TString, clear)(string);
}

//	Memory manager
TString T_CLASS(TString, resize)(TString const string)
{
	const size_t old_size = T_CLASS(TString, size)(string) + 1;
	return T_FUNCTION(resize, char)(string, old_size, old_size + block_size);
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
TString T_CLASS(TString, multy_append)(TString const string, TMessage message)
{
	TString result = string;
	for (size_t index = 0u; index < T_CLASS(TString, size)(message); ++index)
		result = T_CLASS(TString, append)(result, message[index]);
	return result;
}
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
	TString* result = T_FUNCTION(new, TString)(array_size);
	// Extract the first token
	TString token = strtok(message, splitters);
	// loop through the string to extract all other tokens
	while(token != nullptr)
	{
		result = T_FUNCTION(resize, TString)(result, array_size, array_size + 1u);
		result[array_size] = T_CLASS(TString, multy_append)(result[array_size], token);
		array_size += 1;
		token = strtok(message, splitters);
	}
	result = T_FUNCTION(resize, TString)(result, array_size, array_size + 1u);
	return result;
}

#define T_THROW_OUT_OF_RANGE(T_CLASS_NAME, T_CRITICAL, T_RETURN_VALUE) T_THROW_EXCEPTION(T_CLASS_NAME, "Invalid index in " T_CLASS_NAME, E_LOCATION, T_CRITICAL, 0xFE000101, T_RETURN_VALUE)

TString T_CLASS(TString, insert)(TString const container, const size_t index, const char value)
{
	if (index > T_CLASS(TString, size)(container) + 1) T_THROW_OUT_OF_RANGE("TString", false, nullptr);
	T_CLASS(TString, append)(container, value);
	if (index != T_CLASS(TString, size)(container))
		for (size_t i = T_CLASS(TString, size)(container) - 1u; i > index; --i)
			container[i] = container[i - 1u];
	container[index] = value;
	return container;
}

#define T_THROW_BAD_CONVERTION(T_CLASS_NAME, T_NEW_TYPE, T_CRITICAL, T_RETURN_VALUE) T_THROW_EXCEPTION(T_CLASS_NAME, "Invalid index in " T_CLASS_NAME, E_LOCATION, T_CRITICAL, 0xFE0001CF, T_RETURN_VALUE)

/*	Conversions for TMessage (can be used to convert TStrings as well):	*/
// Not message because 'const' is ignored by gcc. But it is still const!
TString T_CONVERTER(TFlag, TString)(const TFlag flag)
{
	return flag == true ? "true" : "false";
}
size_t T_CONVERTER(TString, size_t)(TMessage message)
{
	size_t result = 0u;
	for (size_t i = 0u; message[i] != '\0'; ++i)
	{
		if (message[i] < '0' || message[i] > '9') T_THROW_BAD_CONVERTION("TSting", "size_t", false, 0u);
		result = result * 10 + (message[i] % '0');
	}
	return result;
}

T_IMPORT_MATH_DEFINITION(int)

TString T_CONVERTER(int, TString)(const int value)
{
	TString result = T_CLASS(TString, default_constructor)();
	TFlag is_negative = value < 0;
	for (int temp = abs__int(value); temp > 0; temp /= 10)
		result = T_CLASS(TString, insert)(result, 0u, temp % 10 + '0');
	if (is_negative) result = T_CLASS(TString, insert)(result, 0u, '-');
	return result;
}
