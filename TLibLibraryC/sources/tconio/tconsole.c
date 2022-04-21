#pragma once

#include <stdarg.h>
#include <stdio.h>
#ifdef __linux__
#include <termios.h>
#include <unistd.h>
#endif
#ifdef _WIN32
#include <Windows.h>
#include <conio.h>
#endif

#include "../tconio.h"
#include "../tstring.h"
#include "../tfilesystem.h"

#define T_THROW_TINPUT_INIT T_THROW_EXCEPTION("TConio::TConsole", "TInput cannot be initialized as any of other streams", E_LOCATION, true, 0xCE00C1, )
#define T_THROW_CLOSED_STREM T_THROW_EXCEPTION("TConio::TConsole", "Output stream is closed. Failed to print message", E_LOCATION, true, 0xCE00C0, )

static TFlag is_initialized = false;

static struct TConsole
{
	TFile streams[5];
	TString formats[5];
} t_console;

static TFlag t_debug = false;

TFile T_CLASS(TConsole, defaultof)(const TConsoleId id)
{
	const TFile defaults[] = { stdin, stdout, stderr, stdout, stdout };
	return defaults[id];
}

void T_CLASS(TConsole, destructor)(void)
{
	for (TConsoleId id = kInput; id <= kDebug; ++id)
	{
		if (t_console.streams[id] != T_CLASS(TConsole, defaultof)(id))
			if (id != kOutput || t_console.streams[kOutput] != t_console.streams[kError])
				T_CLASS(TFile, close)(t_console.streams[id], true);
		t_console.streams[id] = nullptr;
		t_console.formats[id] = T_CLASS(TString, destructor)(t_console.formats[id]);
	}
}
void T_CLASS(TConsole, constructor)(TMessage t_input, TMessage t_output, TMessage t_error, TMessage t_log)
{
	if (!is_initialized)
	{
		T_FUNCTION(syscall, atexit)(T_CLASS(TConsole, destructor));
		is_initialized = true;
	}
	else T_CLASS(TConsole, destructor)();
	for (TConsoleId id = kInput; id <= kDebug; ++id)
	{
		t_console.streams[id] = T_CLASS(TConsole, defaultof)(id);
		t_console.formats[id] = nullptr;
	}

	if (t_input != nullptr && (T_CLASS(TString, equal)(t_input, t_output)
		|| T_CLASS(TString, equal)(t_input, t_error)
		|| T_CLASS(TString, equal)(t_input, t_log)))
		T_THROW_TINPUT_INIT

	TMessage file_paths[4] = { t_input, t_output, t_error, t_log }, file_modes[4] = { "r", "w", "w", "a" };
	for (TConsoleId id = kInput; id <= kLog; ++id)
	{
		if (id != kInput) T_CLASS(TFile, touch)(file_paths[id]);
		if (id == kError && file_paths[kError] != nullptr && T_CLASS(TString, equal)(file_paths[kOutput], file_paths[kError]))
			t_console.streams[kError] = t_console.streams[kOutput];
		else if (file_paths[id] != nullptr)
			t_console.streams[id] = T_CLASS(TFile, open)(file_paths[id], file_modes[id], true);
	}
}
void T_CLASS(TConsole, default_constructor)(void)
{
	T_CLASS(TConsole, constructor)(nullptr, nullptr, nullptr, nullptr);
	T_CLASS(TConsole, set_format)(kInput, kNormal, true, kYellow);
	T_CLASS(TConsole, set_format)(kOutput, kNormal, true, kGreen);
	T_CLASS(TConsole, set_format)(kError, kNormal, true, kRed);
	T_CLASS(TConsole, set_format)(kLog, kNormal, true, kCyan);
	T_CLASS(TConsole, set_format)(kDebug, kNormal, true, kPurple);
}


void T_CLASS(TConsole, set_format)(const TConsoleId id, const TAnsiSgr font, const TFlag fg_bright, const TAnsiColor foreground)
{
	if (t_console.streams[id == kInput ? kOutput : id] != T_CLASS(TConsole, defaultof)(id == kInput ? kOutput : id)) return;

	enum TAnsiSgrPrefix
	{
		kSetTextType = '0',	// TYPE
		kUnsetTextType = '2', // TYPE:Do not use with 0
		kSetForegroundColor = '3',	// Color
		//kSetBackgroundColor = '4',	// Color
		kSetBrightForegroundColor = '9',	// Color
		//kSetBrightBackgroundColor // = '10',	// Color
	};

	TString format = T_CLASS(TString, destructor)(t_console.formats[id]);
	TMessage message0 = "\033[0;";
	for (size_t i = 0u; i < T_CLASS(TString, size)(message0); ++i)
		format = T_CLASS(TString, append)(format, message0[i]);
	format = T_CLASS(TString, append)(format, (char)font);
	format = T_CLASS(TString, append)(format, ';');
	format = T_CLASS(TString, append)(format, fg_bright ? kSetBrightForegroundColor : kSetForegroundColor);
	format = T_CLASS(TString, append)(format, (char)foreground);
	format = T_CLASS(TString, append)(format, 'm');
	t_console.formats[id] = format;
}

void T_CLASS(TConsole, format_stream)(const TConsoleId id)
{
	TFile const stream = t_console.streams[id == kInput ? kOutput : id];
	if (stream != T_CLASS(TConsole, defaultof)(id == kInput ? kOutput : id)) return;
	fprintf(stream, "%s", t_console.formats[id]);
}
void T_CLASS(TConsole, unformat_stream)(const TConsoleId id)
{
	TFile const stream = t_console.streams[id == kInput ? kOutput : id];
	if (stream != T_CLASS(TConsole, defaultof)(id == kInput ? kOutput : id)) return;
	fprintf(stream, "\033[9;39;49;0m");
}
void T_CLASS(TConsole, print)(const TConsoleId id, TMessage format, ... )
{
	if (id == kDebug && t_debug == false) return;

	TFile const file = t_console.streams[id == kInput ? kOutput : id];
	if (file == nullptr) T_THROW_CLOSED_STREM

	T_CLASS(TConsole, format_stream)(id);
	va_list ptr;
	va_start(ptr, format);
	vfprintf(file, format, ptr);
	va_end(ptr);
	T_CLASS(TConsole, unformat_stream)(id);
}

TString T_CLASS(TConsole, sprint)(TMessage format, ... )
{
	TString result = T_CLASS(TString, default_constructor)();
	int quantity;
	do
	{
		T_CLASS(TString, destructor)(result);
		T_CLASS(TString, resize)(result);
		va_list ptr;
		va_start(ptr, format);
		quantity = vsnprintf(result, (T_CLASS(TString, size)(result) / 16 + 1) * 16, format, ptr);
		va_end(ptr);
	} while ((size_t)quantity > T_CLASS(TString, size)(result));
	return result;
}

void T_CLASS(TConsole, echo)(const TFlag enabled)
{
#ifdef WIN32
	HANDLE const h_std_in = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(h_std_in, &mode);
	if (enabled) mode |= ENABLE_ECHO_INPUT;
	else mode &= ~ENABLE_ECHO_INPUT;
	SetConsoleMode(h_std_in, mode);
#endif
#ifdef __linux__
	struct termios tty;
	tcgetattr(STDIN_FILENO, &tty);
	if (enabled) tty.c_lflag |= ECHO;
	else tty.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
}

void T_CLASS(TConsole, debug)(const TFlag enabled)
{
	t_debug = enabled;
}

void T_CLASS(TConsole, scan)(TMessage format, ...)
{
	const TConsoleId id = kInput;
	TFile const file = t_console.streams[id];
	if (file == nullptr) T_THROW_CLOSED_STREM

	T_CLASS(TConsole, format_stream)(id);
	va_list ptr;
	va_start(ptr, format);
	vfscanf(file, format, ptr);
	va_end(ptr);
	T_CLASS(TConsole, unformat_stream)(id);
}
void T_CLASS(TConsole, clear)(void)
{
	int ch;
	if (t_console.streams[kInput] == nullptr) return;
	T_CLASS(TConsole, echo)(false);
	while ((ch = fgetc(t_console.streams[kInput])) != '\n' && ch != EOF) {}
	T_CLASS(TConsole, echo)(true);
}
TString T_CLASS(TConsole, getline)(TMessage message, const TFlag can_be_empty)
{
	TString string = nullptr;
	int character = '\0';
	do
	{
		if (character != '\0') T_CLASS(TConsole, print)(kOutput, "An empty string is not allowed!\n");
		if (message != nullptr) T_CLASS(TConsole, print)(kOutput, "Enter the %s: ", message);
		T_CLASS(TConsole, format_stream)(kInput);
		while ((character = fgetc(t_console.streams[kInput])) != '\n' && character != EOF)
			string = T_CLASS(TString, append)(string, (char)character);
		T_CLASS(TConsole, unformat_stream)(kInput);
	} while (can_be_empty == false && T_CLASS(TString, empty)(string));
	return string;
}
TFlag T_CLASS(TConsole, confirmation)(TMessage message)
{
	if (message != nullptr) T_CLASS(TConsole, print)(kOutput, "Are you sure you want to %s? [Y/N] ", message);
	T_CLASS(TConsole, echo)(false);

	TString string = nullptr;
	while (true)
	{
		T_CLASS(TString, destructor)(string);
		string = T_CLASS(TConsole, getline)(nullptr, true);
		if (T_CLASS(TString, equal)(string, "Y") || T_CLASS(TString, equal)(string, "y")
			|| T_CLASS(TString, equal)(string, "N") || T_CLASS(TString, equal)(string, "n"))
			break;
	}
	const char c = string[0];
	T_CLASS(TString, destructor)(string);
	T_CLASS(TConsole, echo)(true);
	T_CLASS(TConsole, print)(kInput, "%c\n", c);
	return c == 'Y' || c == 'y';
}
