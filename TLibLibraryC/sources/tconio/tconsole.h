#pragma once

#include "../tbasic.h"

typedef enum
{
	kInput = 0,
	kOutput,
	kError,
	kLog,
	kDebug,
	kLibrary,
} TConsoleId;
typedef enum
{
	kBlack = '0',// \033[0; 30m
	kRed,// \033[0; 31m
	kGreen,// \033[0; 32m
	kYellow,// \033[0; 33m
	kBlue,// \033[0; 34m
	kPurple,// \033[0; 35m
	kCyan,// \033[0; 36m
	kWhite,// \033[0; 37m
	//kRGB, = '8' - RGB-color: Next arguments are 5;n or 2;r;g;b.
	kDefault = '9',
} TAnsiColor;
typedef enum
{
	// TYPES
	kNormal = '0', // Reset
	kBold = '1', // Bright
	kDim = '2', // Faint, decreased intensity
	kItalic = '3',
	kUnderlined = '4',
	kSlowBlinking = '5',
	kRapidBlinking = '6',
	//kReversed = '7', // Inverted
	kHidden = '8', // Concealed
	kCrossedOut = '9', // Strike
} TAnsiSgr;

void T_CLASS(TConsole, constructor)(TMessage t_input, TMessage t_output, TMessage t_error, TMessage t_log);
void T_CLASS(TConsole, set_format)(const TConsoleId id, const TAnsiSgr font, const TBool fg_bright, const TAnsiColor foreground);
void T_CLASS(TConsole, print)(const TConsoleId id, TMessage format, ... );
void T_CLASS(TConsole, format_stream)(const TConsoleId id);
void T_CLASS(TConsole, unformat_stream)(const TConsoleId id);
void T_CLASS(TConsole, echo)(const TBool enabled);
void T_CLASS(TConsole, debug)(const TBool enabled);
void T_CLASS(TConsole, library)(const TBool enabled);
void T_CLASS(TConsole, scan)(TMessage format, ...);
void T_CLASS(TConsole, clear)(void);
TString T_CLASS(TConsole, getline)(TMessage message, const TBool can_be_empty);
TString T_CLASS(TConsole, getfile)(TFile const file, TMessage message, const TBool can_be_empty);
TBool T_CLASS(TConsole, confirmation)(TMessage message);
