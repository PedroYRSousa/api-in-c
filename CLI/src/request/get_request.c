#include "request.h"
#include <string.h>

t_request	*get_request(char **file)
{
	t_request	*req;
	char		*aux;
	char		*line;

	aux = strstr((*file), "\n");
	if (aux)
	{
		line = strndup((*file), ((aux - (*file)) - 1));
		(*file) = (aux + 1);
		req = create_request(line);
		return (req);
	}
	else
		(*file) = NULL;
	return (NULL);
}
