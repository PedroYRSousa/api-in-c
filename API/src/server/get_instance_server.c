#include "server.h"

t_server	*get_instance_server(void)
{
	static t_server	__instance;

	return (&__instance);
}
