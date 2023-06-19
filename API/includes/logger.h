#ifndef LOGGER_H
# define LOGGER_H

# include "utils.h"
# include <time.h>

typedef struct s_log
{
	t_request		*req;
	t_connection	*conn;
	time_t			mseconds;
}	t_log;

typedef struct s_llog
{
	t_log			log;
	struct s_llog	*next;
}	t_llog;

typedef struct s_logger
{
	int		fd;
	pid_t	pid;
	t_llog	*list;
	char	to_work;
}	t_logger;

void		add_log(t_connection *conn, t_request *req, time_t mseconds);
void		complete_logger(void);
void		write_logger(int sig);
t_logger	*get_instance_logger(void);

#endif