#include "io.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char	*read_log(int fd)
{
	char				*aux;
	char				*file;
	unsigned long		count;
	static char			buffer[BUFFER_SIZE];

	file = NULL;
	while ((count = read(fd, buffer, BUFFER_SIZE)))
	{
		if (file)
		{
			aux = (char *)calloc((count + strlen(file) + 1), sizeof(char));
			strcat(aux, file);
			free(file);
		}
		else
			aux = (char *)calloc((count + 1), sizeof(char));
		strncat(aux, buffer, count);
		file = aux;
	}
	return (file);
}
