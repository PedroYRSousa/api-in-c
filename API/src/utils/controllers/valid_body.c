#include <mongoc.h>
#include "utils.h"

bson_t	*valid_body(t_connection *conn, t_request *req, void (*get_value)(bson_t, bson_t *), char *(*valid)(bson_t *))
{
	bson_t	*body;
	char	*err_msg;

	body = get_body(conn, req, get_value);

	if ((err_msg = valid(body)))
	{
		bson_destroy(body);
		send_msg_error(conn, HTTP_BAD, err_msg);
		return (NULL);
	}

	return (body);
}
