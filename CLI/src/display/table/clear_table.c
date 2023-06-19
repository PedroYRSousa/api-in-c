#include "display/table.h"
#include <stdlib.h>

void	clear_table(t_table	**table)
{
	t_table *aux;

	while ((*table))
	{
		aux = (*table);
		(*table) = (*table)->next;
		free(aux);
	}
	free((*table));
	(*table) = NULL;
}
