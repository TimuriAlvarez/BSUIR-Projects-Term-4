#pragma once

#include "tbasic.h"

/*	Static Const part of TString (aka TMessage)	*/
size_t T_CLASS(TMessage, size)(TMessage message);
TComparison T_CLASS(TMessage, compare)(TMessage message1, TMessage message2);
TFlag T_CLASS(TMessage, equal)(TMessage message1, TMessage message2);
TFlag T_CLASS(TMessage, empty)(TMessage message);
TFlag T_CLASS(TMessage, contains)(TMessage message, const char character);

/*	Dynamic Mutable part of TString (TString itself)	*/
TString T_CLASS(TString, constructor)(TMessage message);
TString T_CLASS(TString, default_constructor)(void);
TString T_CLASS(TString, clear)(TString const string);
TString T_CLASS(TString, destructor)(TString const string);
TString T_CLASS(TString, resize)(TString const string);
TString T_CLASS(TString, append)(TString const string, const char character);
TString T_CLASS(TString, multy_append)(TString const string, TMessage message);
//TString* T_CLASS(TString, chop)(TMessage string, const size_t quentity) { !chop it! }
TString T_CLASS(TString, substring)(TMessage message, const size_t index_start, const size_t index_end);
TString* T_CLASS(TString, split)(TString message, TMessage splitters);

/*	Conversions for TMessage (can be used to convert TStrings as well):	*/
// Not message because 'const' is ignored by gcc. But it is still const!
TString T_CONVERTER(TFlag, TMessage)(const TFlag flag);
size_t T_CONVERTER(TString, size_t)(TMessage message);
int T_CONVERTER(TString, int)(TString message);
