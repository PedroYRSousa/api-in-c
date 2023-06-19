#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

static void	get_secret(t_config *config);
static void	get_log_path(t_config *config);
static void	get_host_server(t_config *config);
static void	get_host_database(t_config *config);
static void	read_file_raw(int fd, char **file_raw);

char	load_config(void)
{
	int			fd;
	t_config	*config;

	config = get_instance_config();
	
	fd = open("/root/labs/API/config/.env", O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);
	read_file_raw(fd, &(config->file_raw));
	close(fd);

	get_secret(config);
	get_log_path(config);
	get_host_server(config);
	get_host_database(config);

	if (!config->secret.ptr || !config->host_server.ptr || !config->host_database.ptr)
		return (EXIT_FAILURE);

	config->secret.ptr[config->secret.size] = 0;
	config->log_path.ptr[config->log_path.size] = 0;
	config->host_server.ptr[config->host_server.size] = 0;
	config->host_database.ptr[config->host_database.size] = 0;

	return (EXIT_SUCCESS);
}


static void	read_file_raw(int fd, char **file_raw)
{
	char		*aux;
	ssize_t		count;
	static char	buffer[BUFFER_SIZE];

	while ((count = read(fd, buffer, BUFFER_SIZE)))
	{
		if ((*file_raw))
		{
			aux = (char *)calloc((count + strlen((*file_raw)) + 1), sizeof(char));
			strcat(aux, (*file_raw));
			free((*file_raw));
		}
		else
			aux = (char *)calloc((count + 1), sizeof(char));
		strncat(aux, buffer, count);
		(*file_raw) = aux;
	}
}

static void	get_log_path(t_config *config)
{
	config->log_path.ptr = (strstr(config->file_raw, "log_path="));
	if (config->log_path.ptr)
	{
		config->log_path.ptr = config->log_path.ptr + strlen("log_path=");
		config->log_path.size = strstr(config->log_path.ptr, "\n") - config->log_path.ptr;
	}
}

static void	get_secret(t_config *config)
{
	config->secret.ptr = (strstr(config->file_raw, "secret="));
	if (config->secret.ptr)
	{
		config->secret.ptr = config->secret.ptr + strlen("secret=");
		config->secret.size = strstr(config->secret.ptr, "\n") - config->secret.ptr;
	}
}

static void	get_host_server(t_config *config)
{
	config->host_server.ptr = (strstr(config->file_raw, "host_server="));
	if (config->host_server.ptr)
	{
		config->host_server.ptr = config->host_server.ptr + strlen("host_server=");
		config->host_server.size = strstr(config->host_server.ptr, "\n") - config->host_server.ptr;
	}
}

static void	get_host_database(t_config *config)
{
	config->host_database.ptr = (strstr(config->file_raw, "host_database="));
	if (config->host_database.ptr)
	{
		config->host_database.ptr = config->host_database.ptr + strlen("host_database=");
		config->host_database.size = strstr(config->host_database.ptr, "\n") - config->host_database.ptr;
	}
}
