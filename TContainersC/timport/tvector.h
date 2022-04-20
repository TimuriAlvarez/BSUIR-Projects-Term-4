#include "tlib.h"

#ifndef CONTAINER_DATA_TYPE
#define CONTAINER_DATA_TYPE int
#endif

#define CONTAINER_TYPE TVector

typedef struct T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX);
typedef T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ALLOCATOR_POSTFIX)* T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX);
typedef CONTAINER_DATA_TYPE* T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX);

//T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_next)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const iterator);
//T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_previous)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const iterator);
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_start)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container);
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_end)(void);
//TFlag T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_last)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const iterator);
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_iterate)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) const iterator);

T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, default_constructor)(void);
TFlag T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, is_empty)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container);
size_t T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, size)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container);
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, at_index)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const size_t index);
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, set_iteration_direction)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const TFlag is_reversed);
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, clear)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container);
T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, destructor)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container);
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, append)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const CONTAINER_DATA_TYPE value, const TFlag append_back);
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, insert)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const size_t index, const CONTAINER_DATA_TYPE value);
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, multy_inset)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const size_t index, const CONTAINER_DATA_TYPE value, const size_t quantity);
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, emplace)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const size_t index, const CONTAINER_DATA_TYPE* const value, const size_t size);
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, chop)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const TFlag chop_back);
void T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, erase)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container, const size_t index);

//T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, copy)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container)
//T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, merge)(T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container1, T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_CONTAINER_POSTFIX) const container2)

#ifndef T_SOURCE_FILE

#undef CONTAINER_TYPE
#undef CONTAINER_DATA_TYPE
#undef T_SOURCE_FILE

#endif
