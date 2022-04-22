#pragma once

#include <malloc.h>

#include "../tconio.h"

#define T_THROW_BADALLOC T_THROW_EXCEPTION("TImport::TMemory::new", "Failed to allocate memory - badalloc", true, 0xCF00BA, { return nullptr; })

/*	WARNING: T_ALLOCATOR_TYPE must be a single identificator (existing type) without any non-letter characters	*/

#define T_IMPORT_MEMORY_DECLARATION(T_ALLOCATOR_TYPE) \
	T_ALLOCATOR_TYPE* T_FUNCTION(new, T_ALLOCATOR_TYPE)(const size_t new_size); \
	T_ALLOCATOR_TYPE* T_FUNCTION(delete, T_ALLOCATOR_TYPE)(T_ALLOCATOR_TYPE* pointer); \
	T_ALLOCATOR_TYPE* T_FUNCTION(resize, T_ALLOCATOR_TYPE)(T_ALLOCATOR_TYPE* pointer, const size_t old_size, const size_t new_size);

#define T_IMPORT_MEMORY_DEFINITION(T_ALLOCATOR_TYPE) \
	T_ALLOCATOR_TYPE* T_FUNCTION(new, T_ALLOCATOR_TYPE)(const size_t new_size) \
	{ \
		if (new_size == 0u) return nullptr; \
		T_ALLOCATOR_TYPE* result = calloc(new_size, sizeof(T_ALLOCATOR_TYPE)); \
		if (result == nullptr) T_THROW_BADALLOC\
		return result; \
	} \
	T_ALLOCATOR_TYPE* T_FUNCTION(delete, T_ALLOCATOR_TYPE)(T_ALLOCATOR_TYPE* pointer) \
	{ \
		if (pointer != nullptr) free(pointer); \
		return nullptr; \
	} \
	T_ALLOCATOR_TYPE* T_FUNCTION(resize, T_ALLOCATOR_TYPE)(T_ALLOCATOR_TYPE* pointer, const size_t old_size, const size_t new_size) \
	{ \
		T_ALLOCATOR_TYPE* result = T_FUNCTION(new, T_ALLOCATOR_TYPE)(new_size); \
		const size_t temp_size = (old_size < new_size ? old_size : new_size); \
		if (pointer != nullptr && result != nullptr) \
			for (size_t index = 0u; index < temp_size; ++index) \
				*(result + index) = *(pointer + index); \
		T_FUNCTION(delete, T_ALLOCATOR_TYPE)(pointer); \
		return result; \
	}
