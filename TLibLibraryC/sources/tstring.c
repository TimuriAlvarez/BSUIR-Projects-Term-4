#include <string.h>

#include "tstring.h"
#include "timport.h"

//	Size of allocation block (number of characters to be allocated/reallocated int the string)
static const size_t block_size = 16u;

/*	Static Const part of TString (aka TMessage)	*/
size_t T_CLASS(TMessage, size)(TMessage message)
{
	size_t counter = 0u;
	if (message != nullptr) while (message[counter] != '\0') ++counter;
	return counter;
}
TComparison T_CLASS(TMessage, compare)(TMessage message1, TMessage message2)
{
	const size_t size1 = T_CLASS(TMessage, size)(message1), size2 = T_CLASS(TMessage, size)(message2);
	for (size_t index = 0u; index < size1 && index < size2; ++index)
	{
		if (message1[index] > message2[index]) return kGreater;
		if (message1[index] < message2[index]) return kLess;
	}
	if (size1 > size2) return kGreater;
	if (size1 < size2) return kLess;
	return kEqual;
}
TFlag T_CLASS(TMessage, equal)(TMessage message1, TMessage message2)
{
	return T_CLASS(TMessage, compare)(message1, message2) == kEqual;
}
TFlag T_CLASS(TMessage, empty)(TMessage message)
{
	return T_CLASS(TMessage, size)(message) == 0u;
}
TFlag T_CLASS(TMessage, contains)(TMessage message, const char character)
{
	for (size_t index = 0u; index < T_CLASS(TMessage, size)(message); ++index)
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
	const size_t old_size = T_CLASS(TMessage, size)(string) + 1;
	return T_FUNCTION(resize, char)(string, old_size, old_size + block_size);
}

TString T_CLASS(TString, append)(TString const string, const char character)
{
	TString result;
	if (T_CLASS(TMessage, size)(string) % block_size == 0 || string == nullptr)
		result = T_CLASS(TString, resize)(string);
	else result = string;
	result[T_CLASS(TMessage, size)(result)] = character;
	return result;
}
TString T_CLASS(TString, multy_append)(TString const string, TMessage message)
{
	TString result = string;
	for (size_t index = 0u; index < T_CLASS(TMessage, size)(message); ++index)
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
		result = result * 10 + (message[i] % '0');
	return result;
}
//int T_CONVERTER(TString, int)(TString message);
