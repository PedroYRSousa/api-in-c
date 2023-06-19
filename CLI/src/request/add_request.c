#include "request.h"

void	add_request(t_request *req, t_request **root)
{
	t_request	*aux;

	if (!req)
		return ;
	if (!(*root))
		(*root) = req;
	else
	{
		aux = (*root);
		while (aux->next)
			aux = aux->next;
		aux->next = req;
	}
}
