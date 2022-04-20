#define T_SOURCE_FILE

#include "tarray.h"

typedef struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX)
{
	CONTAINER_DATA_TYPE* data;
	size_t size;
	TFlag reversed_iteration;
} T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX);

T_IMPORT_MEMORY_DEFINITION(CONTAINER_DATA_TYPE)
T_IMPORT_MEMORY_DEFINITION(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX))

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

T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, constructor)(const size_t size)
{
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const result = T_FUNCTION(new, T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX))(1u);
	result->data = T_FUNCTION(new, CONTAINER_DATA_TYPE)(size);
	result->size = size;
	result->reversed_iteration = false;
	return result;
}

TFlag T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, is_empty)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container)
{
	return container->size == 0u;
}
// Was not removed for code-compatibility
size_t T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, size)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container)
{
	return container->size;
}

T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, at_index)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const size_t index)
{
	if (index >= T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, size)(container)) return nullptr;	/*	TODO:	EXCEPTION	*/
	return container->reversed_iteration ? container->data + container->size - 1 - index : container->data + index;
}
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, set_iteration_direction)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const TFlag is_reversed)
{
	container->reversed_iteration = is_reversed;
}
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, fill)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const CONTAINER_DATA_TYPE value)
{
	for (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_start)(container); iterator != T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_end)();
		iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_iterate)(container, iterator))
		*iterator = value;
}

T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, destructor)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container)
{
	T_FUNCTION(delete, CONTAINER_DATA_TYPE)(container->data);
	return T_FUNCTION(delete, T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX))(container);
}

//T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, copy)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container)
//T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, merge)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container1, T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container2)

#undef CONTAINER_TYPE
#undef CONTAINER_DATA_TYPE
