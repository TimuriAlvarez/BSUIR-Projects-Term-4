#include "dirwalk.h"

extern struct DirWalkOptions flags;

void special_sort(T_CONTAINER(TList, DirEnt_p, T_CONTAINER_POSTFIX) container)
{
	const size_t size = T_CONTAINER(TList, DirEnt_p, size)(container);
	for (size_t gap = size / 2; gap > 0; gap /= 2)
	{
		TBool flag = true;
		while (flag)
		{
			flag = false;
			for (size_t i = 0, j = i + gap; j < size; ++i, ++j)
			{
				T_CONTAINER(TList, DirEnt_p, T_ITERATOR_POSTFIX) const iterator_i = T_CONTAINER(TList, DirEnt_p, at_index)(container, i);
				T_CONTAINER(TList, DirEnt_p, T_ITERATOR_POSTFIX) const iterator_j = T_CONTAINER(TList, DirEnt_p, at_index)(container, j);
				TMessage name1 = (*iterator_i)->d_name;
				TMessage name2 = (*iterator_j)->d_name;
				if (strcoll(name1, name2) > 0)
				{
					const DirEnt_p temp = *iterator_i;
					*iterator_i = *iterator_j;
					*iterator_j = temp;
					flag = true;
				}
			}
		}
	}
}

int dir_walk(TMessage directory)
{
	T_CONTAINER(TList, DirEnt_p, T_CONTAINER_POSTFIX) container = T_CONTAINER(TList, DirEnt_p, constructor)();
	DirEnt_p entry;
	DIR* dp = opendir(directory);
	if (dp == nullptr)
	{
		perror("DIR_WALK_WARNING");
		return -1;
	}
	while ((entry = readdir(dp)))
	{
		if (T_CLASS(TString, equal)(entry->d_name, ".") || T_CLASS(TString, equal)(entry->d_name, "..")) continue;
		if (entry->d_type == DIR_TYPE || (flags.files && entry->d_type == FILE_TYPE) || (flags.links && entry->d_type == LINK_TYPE))
			T_CONTAINER(TList, DirEnt_p, push)(container, entry, true);
	}

	if (flags.sort) special_sort(container);

	FOR_EACH_ITERATOR_FROM(iterator, TList, DirEnt_p, container)
	{
		const int type = (*iterator)->d_type;
		TMessage name = (*iterator)->d_name;
		if (flags.dirs && type == DIR_TYPE)
		{
			T_CLASS(TConsole, print)(kOutput, "%s%c%s\n", directory, '/', name);
		}
		if (flags.files && type == FILE_TYPE)
		{
			T_CLASS(TConsole, print)(kInput, "%s%c%s\n", directory, '/', name);
		}
		if (flags.links && type == LINK_TYPE)
		{
			T_CLASS(TConsole, print)(kLog, "%s%c%s\n", directory, '/', name);
		}
		if (type == DIR_TYPE)
		{
			TString const path = T_CLASS(TString, constructor)("%s/%s", directory, (*iterator)->d_name);
			dir_walk(path);
			T_CLASS(TString, destructor)(path);
		}
	}
	closedir(dp);
	T_CONTAINER(TList, DirEnt_p, destructor)(container);
	return 0;
}
