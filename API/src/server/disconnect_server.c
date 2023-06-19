#include "server.h"

void	disconnect_server(void)
{
	t_server	*server;

	server = get_instance_server();
	mg_mgr_free(&(server->mg_server));
}
