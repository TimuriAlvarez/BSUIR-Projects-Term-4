#include "../tlib.h"

#define CONTAINER_TYPE TDeQueue
//#define ENTRANCE_POINT top	/*	or just:	entrance_point	*/
#define HEAD_N_TAIL
#define POINTER_NEXT
#define POINTER_PREVIOUS

/********************************************/

#ifdef CONTAINER_DATA_POINTER
#ifndef CONTAINER_DATA_TYPE
#define CONTAINER_DATA_TYPE T_POINTER(CONTAINER_DATA_POINTER)
typedef CONTAINER_DATA_POINTER* CONTAINER_DATA_TYPE;
#else
#undef CONTAINER_DATA_TYPE
#endif
#endif

#ifndef CONTAINER_DATA_TYPE
#define CONTAINER_DATA_TYPE int
#endif

struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ELEMENT_POSTFIX)
{
	CONTAINER_DATA_TYPE data;
#ifdef POINTER_NEXT
	struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ELEMENT_POSTFIX)* pointer_next;
#endif
#ifdef POINTER_PREVIOUS
	struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ELEMENT_POSTFIX)* pointer_previous;
#endif
};

typedef struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ELEMENT_POSTFIX)* T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX);

#if (defined(POINTER_NEXT) || defined(POINTER_PREVIOUS))
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_next)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const pointer)
{
#ifdef POINTER_NEXT
	return pointer->pointer_next;
#else
#ifdef POINTER_PREVIOUS
	return pointer->pointer_previous;
#else
	return nullptr;
#endif
#endif
}
#endif

#if (defined(POINTER_NEXT) && defined(POINTER_PREVIOUS))
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_previous)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const pointer)
{
	return pointer->pointer_previous;
}
#endif
/**/

struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)
{
#ifdef ENTRANCE_POINT
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) ENTRANCE_POINT;
#endif
#ifdef HEAD_N_TAIL
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) head;
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) tail;
#endif
#if (defined(POINTER_NEXT) && defined(POINTER_PREVIOUS))
	TFlag reversed_iteration;
#endif
};

T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_start)(const struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* const container)
{
#ifdef HEAD_N_TAIL
	return container->reversed_iteration ? container->tail : container->head;
#endif
#ifdef ENTRANCE_POINT
	return container->ENTRANCE_POINT;
#endif
}
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_end)(void)
{
	return nullptr;
}
TFlag T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_last)(const struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* const container, T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const iterator)
{
#ifdef HEAD_N_TAIL
	if (iterator != (container->reversed_iteration ? container->head : container->tail)) return false;
#endif
#ifdef ENTRANCE_POINT
	if ((container->reversed_iteration ? T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_previous)(iterator) : T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_next)(iterator)) != container->ENTRANCE_POINT) return false;
#endif
	return true;
}
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_iterate)(const struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* const container, T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const iterator)
{
	if (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_last)(container, iterator)) return nullptr;
	return container->reversed_iteration ? T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_previous)(iterator) : T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_next)(iterator);
}
//void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_swap) (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const pointer1, T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const pointer2)
//{
//	const CONTAINER_DATA_TYPE temp = pointer1->data;
//	pointer1->data = pointer2->data;
//	pointer2->data = temp;
//}

struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, constructor)(void)
{
	struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* container = t_new(1, sizeof(struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)));
#ifdef HEAD_N_TAIL
	container->head = container->tail = nullptr;
#endif
#ifdef ENTRANCE_POINT
	container->ENTRANCE_POINT = nullptr;
#endif
	container->reversed_iteration = false;
	return container;
}
TFlag T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, is_empty)(const struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* const container)
{
#ifdef HEAD_N_TAIL
	if (container->head == nullptr)
	{
		if (container->tail == nullptr) return true;
		/*	TODO:	EXCEPTION. ONE IS NULLPTR, THE OTHER IS NOT	*/
	}
#endif
#ifdef ENTRANCE_POINT
	if (container->ENTRANCE_POINT == nullptr) return true;
#endif
	return false;
}
size_t T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, size)(const struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* const container)
{
	size_t result = 0u;
	if (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, is_empty)(container)) return result;
	for (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_start)(container); iterator != T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_end)(); ++result)
		iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_iterate)(container, iterator);
	return result;
}
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, at_index)(const struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* const container, const size_t index)
{
	if (index > T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, size)(container)) return nullptr;	/*	TODO:	EXCEPTION	*/
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_start)(container);
	for (size_t i = 0u; i < index; i++)		//		if index = size -> return nullptr
		iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_iterate)(container, iterator);
	return iterator;
}
#if (defined(POINTER_NEXT) && defined(POINTER_PREVIOUS))
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, set_iteration_direction)(struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* const container, const TFlag is_reversed)
{
	container->reversed_iteration = is_reversed;
}
#endif
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, push)(struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* const container, const CONTAINER_DATA_TYPE value
#if (defined(POINTER_NEXT) && defined(POINTER_PREVIOUS))
	, const TFlag push_back
#endif
	)
{
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const temp = t_new(1, sizeof(struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ELEMENT_POSTFIX)));
	temp->data = value;
	temp->pointer_next = temp->pointer_previous = temp;
	if (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, is_empty)(container))
	{
#ifdef HEAD_N_TAIL
		container->head = container->tail = temp;
#endif
#ifdef ENTRANCE_POINT
		container->ENTRANCE_POINT = temp;
#endif
	}
	else if (container->reversed_iteration)
	{
#ifdef HEAD_N_TAIL
		temp->pointer_previous = container->head;
		container->tail->pointer_previous = temp;
		container->head->pointer_next = temp;
		temp->pointer_next = container->tail;
#endif
#ifdef ENTRANCE_POINT
		temp->pointer_previous = container->ENTRANCE_POINT->pointer_previous;
		container->ENTRANCE_POINT->pointer_previous->pointer_next = temp;
		container->ENTRANCE_POINT->pointer_previous = temp;
		temp->pointer_next = container->ENTRANCE_POINT;
#endif
	}
	else
	{
#ifdef HEAD_N_TAIL
		temp->pointer_next = container->head;
		container->tail->pointer_next = temp;
		container->head->pointer_previous = temp;
		temp->pointer_previous = container->tail;
#endif
#ifdef ENTRANCE_POINT
		temp->pointer_next = container->ENTRANCE_POINT->pointer_next;
		container->ENTRANCE_POINT->pointer_next->pointer_previous = temp;
		container->ENTRANCE_POINT->pointer_next = temp;
		temp->pointer_previous = container->ENTRANCE_POINT;
#endif
	}
#ifdef HEAD_N_TAIL
	if (push_back) container->tail = temp;
	else container->head = temp;
#endif
	//?????????????????????????????????????????????????
}
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, insert)(struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* const container, const size_t index, const CONTAINER_DATA_TYPE value)
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
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const temp = t_new(1, sizeof(struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ELEMENT_POSTFIX)));
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const old =
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, at_index)(container, index);
	temp->data = value;
	temp->pointer_next = old;
	temp->pointer_previous = old->pointer_previous;
	old->pointer_previous = old->pointer_previous->pointer_next = temp;
}
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, multy_inset)(struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* const container, const size_t index, const CONTAINER_DATA_TYPE value, const size_t quantity)
{
	for (size_t i = 0; i < quantity; ++i)
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, insert)(container, index, value);
}
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, emplace)(struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* const container, const size_t index, const CONTAINER_DATA_TYPE* const value, const size_t size)
{
	if (size == 0u) return;	/*	TODO:	EXCEPTION	*/
	for (size_t i = size - 1; i > 0u; --i)
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, insert)(container, index, value[i]);
}
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, pop)(struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* const container
#if (defined(POINTER_NEXT) && defined(POINTER_PREVIOUS))
	, const TFlag pop_back
#endif
	)
{
	if (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, is_empty)(container)) return;	/*	TODO:	EXCEPTION	*/
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const temp = pop_back ? container->tail : container->head;
	if (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, size)(container) == 1u)
	{
#ifdef HEAD_N_TAIL
		container->head = container->tail = nullptr;
#endif
#ifdef ENTRANCE_POINT
		container->ENTRANCE_POINT = nullptr;
#endif
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
	t_delete(temp);
}
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, erase)(struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* const container, const size_t index)
{
	if (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, is_empty)(container)) return;	/*	TODO:	EXCEPTION	*/
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const temp =
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, at_index)(container, index);
	if (temp == nullptr) return;	/*	TODO:	EXCEPTION	*/
	if (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, size)(container) == 1u) container->head = container->tail = nullptr;
	else
	{
		temp->pointer_previous->pointer_next = temp->pointer_next;
		temp->pointer_next->pointer_previous = temp->pointer_previous;
	}
	t_delete(temp);
}
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, clear)(struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* const container)
{
	while (!T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, is_empty)(container))
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, pop)(container, !container->reversed_iteration);
}
struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, destructor)(struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* container)
{
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, clear)(container);
	return t_delete(container);
}

struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, copy)(const struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* const container)
{
	struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* new_container = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, constructor)();
	T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_start)(container);
	while (iterator != T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_end)())
	{
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, push)(new_container, iterator->data, true);
		iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_iterate)(container, iterator);
	}
	return new_container;
}
struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, merge)(const struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* const container1, const struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* const container2)
{
	struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX)* new_container = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, constructor)();
	for (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_start)(container1);
		iterator != T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_end)();
		iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_iterate)(container1, iterator))
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, push)(new_container, iterator->data, true);
	for (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_start)(container2);
		iterator != T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_end)();
		iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_iterate)(container2, iterator))
		T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, push)(new_container, iterator->data, true);
	return new_container;
}


/***********************************************/

#undef CONTAINER_TYPE
#undef ENTRANCE_POINT
#undef HEAD_N_TAIL
#undef POINTER_NEXT
#undef POINTER_PREVIOUS
