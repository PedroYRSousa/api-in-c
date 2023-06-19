#ifndef SERVER_H
# define SERVER_H

#include "utils.h"

typedef struct	s_server
{
	t_mg_server	mg_server;
	char		to_exit;
}	t_server;

char		connect_server(void);
void		disconnect_server(void);
t_server	*get_instance_server(void);

#endif