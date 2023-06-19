#include "utils.h"

bson_t	*get_body(t_connection *conn, t_request *req, void (*get_value)(bson_t, bson_t *))
{
	bson_t	*doc;
	bson_t	*body;

	doc = bson_new();
	body = bson_new();

	if (!json_to_bson(doc, req->body.ptr, req->body.len))
		send_msg_error(conn, HTTP_BAD, "Invalid body.");
	else
		get_value((*doc), body);
	
	bson_destroy(doc);

	return (body);
}
