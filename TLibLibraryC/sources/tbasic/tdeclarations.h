#pragma once

#define nullptr NULL
#define E_LOCATION { __FILE__ , __LINE__ , __func__ }

/*	The usage these definitions outside of safe zone is forbidden!
 *	Those who dare to risk will get plenty of errors and undefined behaviour situations.
 *	Can be supplemented with new useful definitions.
 */

#define T_CAT(T_TOKEN_1, T_TOKEN_2) T_TOKEN_1##_##T_TOKEN_2
#define T_CONCATENATION(T_TOKEN_1, T_TOKEN_2) T_TOKEN_1##__##T_TOKEN_2
#define T_DEFINE(T_TOKEN_1, T_TOKEN_2) T_CAT(T_TOKEN_1, T_TOKEN_2)
#define T_DECL(T_TOKEN_1, T_TOKEN_2) T_CONCATENATION(T_TOKEN_1, T_TOKEN_2)
#define T_DECLARE(T_TOKEN_1, T_TOKEN_2, T_TOKEN_3) T_DECL(T_TOKEN_1, T_DECL(T_TOKEN_2, T_TOKEN_3))

/*	These definitions can (and should) be used anywhere you want to!
 *	Just be careful and keep in mind what you are doing.
 *	Do not spawn duplicates here, unless it is essential for organizing the logic of the lib.
 */

#define T_FUNCTION(T_FUNCTION_NAME, T_FUNCTION_TYPE) T_DECL(T_FUNCTION_NAME, T_FUNCTION_TYPE)
#define T_CLASS(T_CLASS_NAME, T_CLASS_METHOD) T_DECL(T_CLASS_NAME, T_CLASS_METHOD)
#define T_CONTAINER(T_CONTAINER_NAME, T_DATA_TYPE, T_CONTAINER_METHOD) T_DECLARE(T_CONTAINER_NAME, T_DATA_TYPE, T_CONTAINER_METHOD)
#define T_CONVERTER(T_OLD_TYPE, T_NEW_TYPE) T_DECLARE(T_OLD_TYPE, to, T_NEW_TYPE)
#define T_ARRAY_SIZE(arr) (size_t)(sizeof(arr) / sizeof((arr)[0]))
#define T_POINTER(T_TYPE) CAT(T_TYPE, p)

/*	These definitions are actually literals, used for identifier generation.
 *	Can be supplemented with other ones if it is necessary.
 */

#define T_CONTAINER_POSTFIX Container
#define T_ALLOCATOR_POSTFIX Allocator
#define T_ITERATOR_POSTFIX Iterator
#define T_ELEMENT_POSTFIX Element

#define FOR_EACH_ITERATOR_FROM(var_iterator, CONTAINER_TYPE, CONTAINER_DATA_TYPE, var_container)\
    for (T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, T_ITERATOR_POSTFIX) var_iterator =\
        T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_start)(var_container);\
        var_iterator != T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_end)();\
        var_iterator = T_CONTAINER(CONTAINER_TYPE, CONTAINER_DATA_TYPE, Iterator_iterate)(var_container, var_iterator))
