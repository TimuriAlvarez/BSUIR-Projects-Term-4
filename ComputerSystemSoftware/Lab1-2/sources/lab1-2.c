#include "lab1-2.h"

typedef struct dirent DirEnt;
#define CONTAINER_DATA_POINTER DirEnt
#include "../../../TLibLibraryC/timport/tlist.h"

#include <stdio.h>
#include <string.h>

void special_sort(const struct T_CONTAINER(TList, DirEnt_p, T_CONTAINER_POSTFIX)* const list)
{
	const size_t size = T_CONTAINER(TList, DirEnt_p, size)(list);
	for (size_t gap = size / 2; gap > 0; gap /= 2)
	{
		TFlag flag = true;
		while (flag)
		{
			flag = false;
			for (size_t i = 0, j = i + gap; j < size; ++i, ++j)
			{
				T_CONTAINER(TList, DirEnt_p, T_ITERATOR_POSTFIX) const iterator_i = T_CONTAINER(TList, DirEnt_p, at_index)(list, i);
				T_CONTAINER(TList, DirEnt_p, T_ITERATOR_POSTFIX) const iterator_j = T_CONTAINER(TList, DirEnt_p, at_index)(list, j);
				TMessage name1 = iterator_i->data->d_name;
				TMessage name2 = iterator_j->data->d_name;
				if (strcoll(name1, name2) > 0)
				{
					T_CONTAINER(TList, DirEnt_p, Iterator_swap)(iterator_i, iterator_j);
					flag = true;
				}
			}
		}
	}
}
char* make_path(TMessage directory, TMessage syb_directory)
{
	char* result = t_new(T_CLASS(TMessage, size)(directory) + T_CLASS(TMessage, size)(syb_directory) + 2, sizeof(char));
	size_t j = 0;
	for (size_t i = 0; i < T_CLASS(TMessage, size)(directory); ++i, ++j) result[j] = directory[i];
	result[j] = '/'; ++j;
	for (size_t i = 0; i < T_CLASS(TMessage, size)(syb_directory); ++i, ++j) result[j] = syb_directory[i];
	return result;
}
int dir_walk(TMessage directory)
{
	struct T_CONTAINER(TList, DirEnt_p, T_CONTAINER_POSTFIX)* list = T_CONTAINER(TList, DirEnt_p, constructor)();
	DirEnt* entry;
	DIR* dp = opendir(directory);
	if (dp == NULL)
	{
		perror("DIR_WALK_WARNING");
		return -1;
	}
	while ((entry = readdir(dp)))  // NOLINT(concurrency-mt-unsafe)
	{
		if (TMessage__equal(entry->d_name, ".") || TMessage__equal(entry->d_name, "..")) continue;
		if (entry->d_type == DIR_TYPE || (flags.files && entry->d_type == FILE_TYPE) || (flags.links && entry->d_type == LINK_TYPE))
			T_CONTAINER(TList, DirEnt_p, push)(list, entry, true);
	}

	if (flags.sort) special_sort(list);

	for (T_CONTAINER(TList, DirEnt_p, T_ITERATOR_POSTFIX) iterator = T_CONTAINER(TList, DirEnt_p, Iterator_start)(list);
		iterator != T_CONTAINER(TList, DirEnt_p, Iterator_end)(); iterator = T_CONTAINER(TList, DirEnt_p, Iterator_iterate)(list, iterator))
	{
		const int type = iterator->data->d_type;
		TMessage name = iterator->data->d_name;
		if ((flags.dirs && type == DIR_TYPE) || (flags.files && type == FILE_TYPE) || (flags.links && type == LINK_TYPE))
		{
			printf("%s%c%s\n", directory, '/', name);
		}
		if (type == 4)
		{
			char* const path = make_path(directory, iterator->data->d_name);
			dir_walk(path);
			t_delete(path);
		}
	}
	closedir(dp);
	T_CONTAINER(TList, DirEnt_p, destructor)(list);
	return 0;
}
