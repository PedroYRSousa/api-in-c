#include "display/list.h"
#include <stdlib.h>

void	clear_list(t_list	**list)
{
	t_list *aux;

	while ((*list))
	{
		aux = (*list);
		(*list) = (*list)->next;
		free(aux);
	}
	free((*list));
	(*list) = NULL;
}
