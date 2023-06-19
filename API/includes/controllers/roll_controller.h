#ifndef ROLL_CONTROLLER_H
# define ROLL_CONTROLLER_H

#include "utils.h"

void	list_roll(t_connection *conn, t_request *req);
void	get_roll(t_connection *conn, t_request *req);
void	create_roll(t_connection *conn, t_request *req);
void	delete_roll(t_connection *conn, t_request *req);

#endif