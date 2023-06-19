#include "display.h"
#include <stdio.h>
#include <string.h>

void	set_color(t_config config, t_list *list)
{
	if (config.is_colored == 1)
	{
		if (strncmp(list->raw.method.ptr, "GET", list->raw.method.size) == 0)
			printf("\e[%dm", COLOR_GET);
		if (strncmp(list->raw.method.ptr, "POST", list->raw.method.size) == 0)
			printf("\e[%dm", COLOR_POST);
		if (strncmp(list->raw.method.ptr, "PUT", list->raw.method.size) == 0)
			printf("\e[%dm", COLOR_PUT);
		if (strncmp(list->raw.method.ptr, "DELETE", list->raw.method.size) == 0)
			printf("\e[%dm", COLOR_DELETE);
		if (strncmp(list->raw.method.ptr, "OTHERS", list->raw.method.size) == 0)
			printf("\e[%dm", COLOR_OTHERS);
	}
}
