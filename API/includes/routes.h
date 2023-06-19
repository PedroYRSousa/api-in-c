#ifndef ROUTES_H
# define ROUTES_H

#include "utils.h"

void	get_routes(t_request *req, void (**route)(t_connection *conn, t_request *req));

#endif