#include "tvector.h"

#ifndef CONTAINER_DATA_TYPE
#define CONTAINER_DATA_TYPE int
#endif

#define CONTAINER_TYPE TVector

typedef struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX)
{
	CONTAINER_DATA_TYPE* data;
	size_t size;
	TFlag reversed_iteration;
} T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX);
typedef T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX)* T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX);

T_IMPORT_MEMORY_DEFINITION(CONTAINER_DATA_TYPE)
T_IMPORT_MEMORY_DEFINITION(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX))

typedef CONTAINER_DATA_TYPE* T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX);

T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_next)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const iterator)
{
	return iterator + 1;
}
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_previous)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const iterator)
{
	return iterator - 1;
}
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_start)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container)
{
	return container->reversed_iteration ? container->data + container->size - 1 : container->data;
}
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_end)(void)
{
	return nullptr;
}
TFlag T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_last)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const iterator)
{
	if (iterator == container->data + (container->reversed_iteration ? 0u : container->size - 1)) return true;
	return false;
}
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_iterate)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const iterator)
{
	if (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_last)(container, iterator)) return nullptr;
	return container->reversed_iteration ? T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_previous)(iterator) : T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_next)(iterator);
}

//OK
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, constructor)(void)
{
	return T_FUNCTION(new, T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX))(1u);
}
//OK
TFlag T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, is_empty)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container)
{
	return container->size == 0u || container->data == nullptr;
}
// OK Was not removed for code-compatibility
size_t T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, size)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container)
{
	return container->size;
}
// +-OK
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, at_index)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const size_t index)
{
	if (index >= T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, size)(container)) return nullptr;
	/*	TODO:	EXCEPTION	*/
	return container->reversed_iteration ? container->data + container->size - 1 - index : container->data + index;
}
//OK
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, set_iteration_direction)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const TFlag is_reversed)
{
	container->reversed_iteration = is_reversed;
}
//OK
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, clear)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container)
{
	container->data = T_FUNCTION(delete, CONTAINER_DATA_TYPE)(container->data);
	container->size = 0u;
}
//OK
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, destructor)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container)
{
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, clear)(container);
	return T_FUNCTION(delete, T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX))(container);
}


//?////////////////////////////////////////////////////////////////////////////////////////////////////
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, append)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const CONTAINER_DATA_TYPE value, const TFlag append_back)
{
	/*	TODO:	Reversed	*/
	container->data = T_FUNCTION(resize, CONTAINER_DATA_TYPE)(container->data, container->size, container->size + 1);
	if (append_back) container->data[container->size] = value;
	else
	{
		for (size_t index = container->size; index > 0u; --index) container->data[index] = container->data[index - 1u];
		container->data[0u] = value;
	}
	container->size = container->size + 1u;
}
// Insert a value by index
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, insert)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const size_t index, const CONTAINER_DATA_TYPE value)
{
	/*	TODO:	Reversed	*/
	if (index > container->size) return; /*	TODO: Exception	*/
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, append)(container, value, true);
	if (index != container->size)
		for (size_t i = container->size - 1u; i > index; --i)
			container->data[i] = container->data[i - 1u];
	container->data[index] = value;
}
// OK Insert but several times
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, multy_inset)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const size_t index, const CONTAINER_DATA_TYPE value, const size_t quantity)
{
	/*	TODO:	Reversed	*/
	for (size_t i = 0; i < quantity; ++i)
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, insert)(container, index, value);
}
//
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, emplace)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const size_t index, const CONTAINER_DATA_TYPE* const value, const size_t size)
{
	/*	TODO:	Reversed	*/
	for (size_t i = size - 1; i > 0u; --i)
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, insert)(container, index, value[i]);
}
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, chop)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const TFlag chop_back)
{
	/*	TODO:	Reversed	*/
	if (container->size == 0u) return; /*	TODO:	Exception	*/
	if (container->size == 1u)
	{
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, clear)(container);
		return;
	}
	if (!chop_back)
		for (size_t index = 1u; index < container->size; ++index)
			container->data[index - 1u] = container->data[index];
	container->data = T_FUNCTION(resize, CONTAINER_DATA_TYPE)(container->data, container->size, container->size - 1u);
	container->size  = container->size - 1u;
}
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, erase)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const size_t index)
{
	/*	TODO:	Reversed	*/
	if (index >= container->size) return; /*	TODO:	Exception	*/
	for (size_t i = index + 1u; i < container->size; ++i)
		container->data[i - 1u] = container->data[i];
	container->data = T_FUNCTION(resize, CONTAINER_DATA_TYPE)(container->data, container->size, container->size - 1u);
	container->size = container->size - 1u;
}

//T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, copy)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container)
//T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, merge)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container1, T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container2)

#undef CONTAINER_TYPE
#undef CONTAINER_DATA_TYPE
