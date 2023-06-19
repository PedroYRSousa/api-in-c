#include "utils.h"
#include "server.h"
#include "config.h"
#include "routes.h"
#include "logger.h"

static void	handle_listen(t_connection *conn, int ev, void *ev_data, void *fn_data);

char	connect_server(void)
{
	t_server	*server;
	t_config	config;

	config = (*get_instance_config());
	server = get_instance_server();
	mg_mgr_init(&(server->mg_server));
	mg_http_listen(&(server->mg_server), config.host_server.ptr, handle_listen, &(server->mg_server));

	if (!server->mg_server.conns)
	{
		return (EXIT_FAILURE);
	}

	write(STDOUT_FILENO, "The server is listening on: ", strlen("The server is listening on: "));
	write(STDOUT_FILENO, config.host_server.ptr, config.host_server.size);
	write(STDOUT_FILENO, "\n", strlen("\n"));

	while (!(server->to_exit))
		mg_mgr_poll(&(server->mg_server), 1000);

	return (EXIT_SUCCESS);
}

static void	handle_listen(t_connection *conn, int ev, void *ev_data, void *fn_data)
{
	struct timeval	end;
	struct timeval	start;
	void			(*route)(t_connection *conn, t_request *req) = NULL;

	(void)fn_data;
	if (ev == MG_EV_HTTP_MSG)
	{
		gettimeofday(&start, NULL);
		get_routes(((t_request *)ev_data), &route);
		route(conn, ((t_request *)ev_data));
		gettimeofday(&end, NULL);
		add_log(conn, ((t_request *)ev_data), ((end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec));
	}
}
