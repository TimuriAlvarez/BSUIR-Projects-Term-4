#define T_SOURCE_FILE

#include "tlist.h"

typedef struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ELEMENT_POSTFIX)
{
	CONTAINER_DATA_TYPE data;
	struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ELEMENT_POSTFIX)* pointer_next;
	struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ELEMENT_POSTFIX)* pointer_previous;
} T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ELEMENT_POSTFIX), *T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_IPRIVATE_POSTFIX);
typedef struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX)
{
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_IPRIVATE_POSTFIX) head;
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_IPRIVATE_POSTFIX) tail;
	TBool reversed_iteration;
} T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX), *T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX);

T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_next)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const pointer)
{
	return (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX))((T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_IPRIVATE_POSTFIX))pointer)->pointer_next;
}
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_previous)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const pointer)
{
	return (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX))((T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_IPRIVATE_POSTFIX))pointer)->pointer_previous;
}

T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_start)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container)
{
	return (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX))(container->reversed_iteration ? container->tail : container->head);
}
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_end)(void)
{
	return nullptr;
}
TBool T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_last)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const iterator)
{
	if (iterator != (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX))(container->reversed_iteration ? container->head : container->tail)) return false;
	return true;
}
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_iterate)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const iterator)
{
	if (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_last)(container, iterator)) return nullptr;
	return container->reversed_iteration ? T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_previous)(iterator) : T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_next)(iterator);
}

T_IMPORT_MEMORY_DEFINITION(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX))

T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, constructor)(void)
{
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) container = T_MEMORY_MANAGER(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX), allocate)(1);

	container->head = container->tail = nullptr;
	container->reversed_iteration = false;
	return container;
}
TBool T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, is_empty)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container)
{
	if (container == nullptr) return true;
	if (container->head == nullptr)
	{
		if (container->tail == nullptr) return true;
		/*	TODO:	EXCEPTION. ONE IS NULLPTR, THE OTHER IS NOT	*/
	}
	return false;
}
size_t T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, size)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container)
{
	size_t result = 0u;
	if (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, is_empty)(container)) return result;
	for (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_start)(container); iterator != T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_end)(); ++result)
		iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_iterate)(container, iterator);
	return result;
}
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, at_index)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const size_t index)
{
	if (index > T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, size)(container)) return nullptr;	/*	TODO:	EXCEPTION	*/
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_start)(container);
	for (size_t i = 0u; i < index; i++)		//		if index = size -> return nullptr
		iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_iterate)(container, iterator);
	return iterator;
}
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, set_iteration_direction)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const TBool is_reversed)
{
	container->reversed_iteration = is_reversed;
}

T_IMPORT_MEMORY_DEFINITION(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ELEMENT_POSTFIX))

void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, push)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const CONTAINER_DATA_TYPE value, const TBool push_back)
{
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_IPRIVATE_POSTFIX) const temp = T_MEMORY_MANAGER(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ELEMENT_POSTFIX), allocate)(1);
	temp->data = value;
	temp->pointer_next = temp->pointer_previous = temp;
	if (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, is_empty)(container))
	{
		container->head = container->tail = temp;
	}
	else if (container->reversed_iteration)
	{
		temp->pointer_previous = container->head;
		container->tail->pointer_previous = temp;
		container->head->pointer_next = temp;
		temp->pointer_next = container->tail;
	}
	else
	{
		temp->pointer_next = container->head;
		container->tail->pointer_next = temp;
		container->head->pointer_previous = temp;
		temp->pointer_previous = container->tail;
	}
	if (push_back) container->tail = temp;
	else container->head = temp;
}
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, insert)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const size_t index, const CONTAINER_DATA_TYPE value)
{
	if (index == 0u)
	{
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, push)(container, value, false);
		return;
	}
	if (index == T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, size)(container))
	{
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, push)(container, value, true);
		return;
	}
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_IPRIVATE_POSTFIX) const temp = T_MEMORY_MANAGER(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ELEMENT_POSTFIX), allocate)(1);
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_IPRIVATE_POSTFIX) const old = (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_IPRIVATE_POSTFIX))T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, at_index)(container, index);
	temp->data = value;
	temp->pointer_next = old;
	temp->pointer_previous = old->pointer_previous;
	old->pointer_previous = old->pointer_previous->pointer_next = temp;
}
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, multy_inset)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const size_t index, const CONTAINER_DATA_TYPE value, const size_t quantity)
{
	for (size_t i = 0; i < quantity; ++i)
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, insert)(container, index, value);
}
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, emplace)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const size_t index, const CONTAINER_DATA_TYPE* const value, const size_t size)
{
	if (size == 0u) return;	/*	TODO:	EXCEPTION	*/
	for (size_t i = size - 1; i > 0u; --i)
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, insert)(container, index, value[i]);
}
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, pop)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const TBool pop_back)
{
	if (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, is_empty)(container)) return;	/*	TODO:	EXCEPTION	*/
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_IPRIVATE_POSTFIX) const temp = pop_back ? container->tail : container->head;
	if (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, size)(container) == 1u)
	{
		container->head = container->tail = nullptr;
	}
	else if (pop_back)
	{
		if (container->reversed_iteration)
		{
			temp->pointer_next->pointer_previous = container->head;
			container->tail = container->head->pointer_next = temp->pointer_next;
		}
		else
		{
			temp->pointer_previous->pointer_next = container->head;
			container->tail = container->head->pointer_previous = temp->pointer_previous;
		}
	}
	else
	{
		if (container->reversed_iteration)
		{
			container->tail->pointer_previous = temp->pointer_previous;
			temp->pointer_previous->pointer_next = container->tail;
			container->head = temp->pointer_previous;
		}
		else
		{
			container->tail->pointer_next = temp->pointer_next;
			temp->pointer_next->pointer_previous = container->tail;
			container->head = temp->pointer_next;
		}
	}
	T_MEMORY_MANAGER(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ELEMENT_POSTFIX), deallocate)(temp);
}
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, erase)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const size_t index)
{
	if (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, is_empty)(container)) return;	/*	TODO:	EXCEPTION	*/
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_IPRIVATE_POSTFIX) const temp = (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_IPRIVATE_POSTFIX))T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, at_index)(container, index);
	if (temp == nullptr) return;	/*	TODO:	EXCEPTION	*/
	if (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, size)(container) == 1u) container->head = container->tail = nullptr;
	else
	{
		temp->pointer_previous->pointer_next = temp->pointer_next;
		temp->pointer_next->pointer_previous = temp->pointer_previous;
	}
	T_MEMORY_MANAGER(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ELEMENT_POSTFIX), deallocate)(temp);
}
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, clear)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container)
{
	while (!T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, is_empty)(container))
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, pop)(container, !container->reversed_iteration);
}
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, destructor)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) container)
{
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, clear)(container);
	return T_MEMORY_MANAGER(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX), deallocate)(container);
}

/*T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, copy)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container)
{
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) new_container = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, constructor)();
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_IPRIVATE_POSTFIX) iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_start)(container);
	while (iterator != T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_end)())
	{
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, push)(new_container, iterator->data, true);
		iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_iterate)(container, iterator);
	}
	return new_container;
}
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, merge)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container1, T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container2)
{
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) new_container = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, constructor)();
	for (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_IPRIVATE_POSTFIX) iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_start)(container1);
		iterator != T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_end)();
		iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_iterate)(container1, iterator))
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, push)(new_container, iterator->data, true);
	for (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_IPRIVATE_POSTFIX) iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_start)(container2);
		iterator != T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_end)();
		iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_iterate)(container2, iterator))
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, push)(new_container, iterator->data, true);
	return new_container;
}*/

#undef CONTAINER_TYPE
#undef CONTAINER_DATA_TYPE
#undef T_SOURCE_FILE
