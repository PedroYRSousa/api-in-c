#include <stdio.h>
#include "config.h"
#include "logger.h"
#include "server.h"
#include "database.h"

static void	handle_signal(int sig);

int	main(void)
{
	if (load_config())
	{
		fprintf(stderr, "Invalid settings.\n");
		return (0);
	}

	if(connect_database() == EXIT_FAILURE)
	{
		disconnect_database();
		fprintf(stderr, "Unable to connect to the database.\n");
		clear_config();
		return (0);
	}

	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGUSR1, write_logger);

	if(connect_server() == EXIT_FAILURE)
	{
		disconnect_server();
		disconnect_database();
		return (0);
	}

	clear_config();
	complete_logger();
	disconnect_server();
	disconnect_database();

	return (0);
}

static void	handle_signal(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
		get_instance_server()->to_exit = 1;
}
