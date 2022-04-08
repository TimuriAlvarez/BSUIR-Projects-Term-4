#pragma once

#include "../tconio.h"

#define T_IMPORT_MENU_DECLARATION(T_MENU_PARAMETERS) \
	typedef void (*T_CONTAINER(TMenu, T_MENU_PARAMETERS, Action))(T_MENU_PARAMETERS*); \
	void T_CONTAINER(TMenu, T_MENU_PARAMETERS, menu_bar)(T_MENU_PARAMETERS* parameters); \
	void T_CONTAINER(TMenu, T_MENU_PARAMETERS, menu)(TMessage* const options, const T_CONTAINER(TMenu, T_MENU_PARAMETERS, Action)* const actions, T_MENU_PARAMETERS* const parameters);

// Attention: T_CONTAINER(TMenu, T_MENU_PARAMETERS, menu_bar)(T_MENU_PARAMETERS* parameters);
// Must be defined mannually!

#define T_IMPORT_MENU_DEFINITION(T_MENU_PARAMETERS) \
	void T_CONTAINER(TMenu, T_MENU_PARAMETERS, menu)(TMessage* const options, const T_CONTAINER(TMenu, T_MENU_PARAMETERS, Action)* const actions, T_MENU_PARAMETERS* const parameters) \
	{ \
		while (true) \
		{ \
			T_CONTAINER(TMenu, T_MENU_PARAMETERS, menu_bar)(parameters); \
			T_CLASS(TConsole, print)(kOutput, "Menu options:\n"); \
			size_t size = 0u; \
			while (options[size] != nullptr) \
			{ \
				T_CLASS(TConsole, print)(kOutput, "\t%zu)\t%s;\n", size + 1, options[size]); \
				++size; \
			} \
			T_CLASS(TConsole, print)(kOutput, "\t%zu)\t%s.\n", size + 1, "Quit"); \
			++size; \
			size_t option; \
			do \
			{ \
				TString const string = T_CLASS(TConsole, getline)("option number", false); \
				option = T_CONVERTER(TString, size_t)(string); \
				T_CLASS(TString, clear)(string); \
			} while (option == 0u || option > size); \
			if (option == size) return; \
			actions[--option](parameters); \
			syscall__update(); \
		} \
	}
