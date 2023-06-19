#ifndef USER_CONTROLLER_H
# define  USER_CONTROLLER_H

#include "utils.h"

void	get_user(t_connection *conn, t_request *req);
void	create_user(t_connection *conn, t_request *req);
void	update_user(t_connection *conn, t_request *req);
void	delete_user(t_connection *conn, t_request *req);

#endif