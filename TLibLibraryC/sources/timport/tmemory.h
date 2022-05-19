#pragma once

#include <malloc.h>

#include "../tconio.h"

/*	WARNING: T_ALLOCATOR_TYPE must be a single identificator (existing type) without any non-letter characters	*/

#define T_MEMORY_MANAGER(T_ALLOCATOR_TYPE, T_MEMORY_FUNCTION) T_CONTAINER(TMemoryManager, T_ALLOCATOR_TYPE, T_MEMORY_FUNCTION)

#define T_IMPORT_MEMORY_DECLARATION(T_ALLOCATOR_TYPE) \
	T_ALLOCATOR_TYPE* T_MEMORY_MANAGER(T_ALLOCATOR_TYPE, allocate)(const size_t size); \
	T_ALLOCATOR_TYPE* T_MEMORY_MANAGER(T_ALLOCATOR_TYPE, deallocate)(T_ALLOCATOR_TYPE* pointer); \
	T_ALLOCATOR_TYPE* T_MEMORY_MANAGER(T_ALLOCATOR_TYPE, reallocate)(T_ALLOCATOR_TYPE* pointer, const size_t old_size, const size_t new_size);

#define T_IMPORT_MEMORY_DEFINITION(T_ALLOCATOR_TYPE) \
	T_ALLOCATOR_TYPE* T_MEMORY_MANAGER(T_ALLOCATOR_TYPE, allocate)(const size_t size) \
	{ \
		if (size == 0u) return nullptr; \
		T_ALLOCATOR_TYPE* result = calloc(size, sizeof(T_ALLOCATOR_TYPE)); \
		if (result == nullptr) T_THROW_EXCEPTION("TMemoryManager::allocate", "BADALLOC: Failed to allocate memory", true, 0xCF00BA, return nullptr; ) \
		return result; \
	} \
	T_ALLOCATOR_TYPE* T_MEMORY_MANAGER(T_ALLOCATOR_TYPE, deallocate)(T_ALLOCATOR_TYPE* pointer) \
	{ \
		if (pointer != nullptr) free(pointer); \
		return nullptr; \
	} \
	T_ALLOCATOR_TYPE* T_MEMORY_MANAGER(T_ALLOCATOR_TYPE, reallocate)(T_ALLOCATOR_TYPE* pointer, const size_t old_size, const size_t new_size) \
	{ \
		T_ALLOCATOR_TYPE* result = T_MEMORY_MANAGER(T_ALLOCATOR_TYPE, allocate)(new_size); \
		const size_t temp_size = (old_size < new_size ? old_size : new_size); \
		if (pointer != nullptr && result != nullptr) \
			for (size_t index = 0u; index < temp_size; ++index) \
				*(result + index) = *(pointer + index); \
		T_MEMORY_MANAGER(T_ALLOCATOR_TYPE, deallocate)(pointer); \
		return result; \
	}
