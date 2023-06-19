#include "display/table.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
static char	contains_row(t_table **table, t_list *row)
{
	unsigned long	uri_len;
	char			*uri_ptr;
	unsigned long	method_len;
	char			*method_ptr;
	t_table			*aux;

	aux = (*table);
	while (aux)
	{
		uri_ptr = row->raw.uri.ptr;
		uri_len = row->raw.uri.size;
		method_ptr = row->raw.method.ptr;
		method_len = row->raw.method.size;

		if (aux->row->raw.uri.size == uri_len && aux->row->raw.method.size == method_len)
		{
			if (strncmp(uri_ptr, aux->row->raw.uri.ptr, uri_len) == 0)
			{
				if (strncmp(method_ptr, aux->row->raw.method.ptr, method_len) == 0)
				{
					aux->count++;
					return (1);
				}
			}
		}
		aux = aux->next;
	}
	return (0);
}

static void	add_row_table(t_table **table, t_list *row)
{
	t_table	*aux;

	if (!(*table))
	{
		(*table) = (t_table *)calloc(1, sizeof(t_table));
		(*table)->count = 1;
		(*table)->row = row;
	}
	else
	{
		aux = (*table);
		while (aux->next)
			aux = aux->next;
		aux->next = (t_table *)calloc(1, sizeof(t_table));
		aux->next->count = 1;
		aux->next->row = row;
	}
}

t_table	*init_table(t_list *list)
{
	t_table	*table;

	table = NULL;
	while (list)
	{
		if (!contains_row(&table, list))
			add_row_table(&table, list);
		list = list->next;
	}
	return (table);
}