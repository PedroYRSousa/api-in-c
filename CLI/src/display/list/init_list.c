#include "display/list.h"
#include <stdlib.h>
#include <string.h>

static char is_small(t_string ref, t_string target)
{
	if (strncmp(ref.ptr, target.ptr, ref.size) <= 0)
		return (1);
	return (0);
}

static void	add_row_dec(t_list *row, t_list **list)
{
	t_list	*aux_1;
	t_list	*aux_2;

	if (!(*list) || !is_small(row->raw.uri, (*list)->raw.uri))
	{
		row->next = (*list);
		(*list) = row;
	}
	else
	{
		aux_1 = (*list);
		aux_2 = (*list);
		while (aux_1 && is_small(row->raw.uri, aux_1->raw.uri))
			aux_1 = aux_1->next;
		while (aux_2->next && aux_2->next != aux_1)
			aux_2 = aux_2->next;
		row->next = aux_2->next;
		aux_2->next = row;
	}
}

static void	add_row_asc(t_list *row, t_list **list)
{
	t_list	*aux_1;
	t_list	*aux_2;

	if (!(*list) || is_small(row->raw.uri, (*list)->raw.uri))
	{
		row->next = (*list);
		(*list) = row;
	}
	else
	{
		aux_1 = (*list);
		aux_2 = (*list);
		while (aux_1 && !is_small(row->raw.uri, aux_1->raw.uri))
			aux_1 = aux_1->next;
		while (aux_2->next && aux_2->next != aux_1)
			aux_2 = aux_2->next;
		row->next = aux_2->next;
		aux_2->next = row;
	}
}

static void	add_row(t_list *row, t_list **list)
{
	t_list	*aux;

	if (!(*list))
		(*list) = row;
	else
	{
		aux = (*list);
		while (aux->next)
			aux = aux->next;
		aux->next = row;
	}
}

t_list	*init_list(t_config config, t_request *requests)
{
	t_list	*row;
	t_list	*list;

	list = NULL;
	while (requests)
	{
		row = (t_list *)calloc(1, sizeof(t_list));
		row->raw = requests->raw;
		row->next = NULL;
		if (config.is_ordened == 0)
			add_row(row, &list);
		if (config.is_ordened == 1)
			add_row_asc(row, &list);
		if (config.is_ordened == 2)
			add_row_dec(row, &list);
		requests = requests->next;
	}
	return (list);
}
