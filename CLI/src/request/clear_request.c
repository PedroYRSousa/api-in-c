#include "request.h"
#include <stdlib.h>

void	clear_request(t_request **root)
{
	t_request *aux;

	while ((*root))
	{
		aux = (*root);
		(*root) = (*root)->next;
		free((void *)aux->raw.data);
		free(aux);
	}
	
	free((*root));
	(*root) = NULL;
}
