#include "io.h"
#include "request.h"
#include "display.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void	clear_console(void)
{
	system("clear");
}

int main(int argc, char **argv)
{
	int			fd;
	char		*file;
	t_request	*requests;

	(void)argc;
	requests = NULL;
	fd = open("../LOG.txt", O_RDONLY, 0666);
	clear_console();
	if (fd > 0)
	{
		file = read_log(fd);
		load_requests(file, &requests);
		display_log(load_config(argv), requests);
		close(fd);
		free(file);
		clear_request(&requests);
	}
	else
		printf("No logs to show!\n");
	return (0);
}
