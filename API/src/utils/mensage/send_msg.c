#include "utils.h"

void	send_msg(t_connection *conn, int HTTP_code, char *msg)
{
	mg_http_reply(conn, HTTP_code, 
		"Content-Type: application/json\n\
Connection: close\n\
Access-Control-Allow-Origin: *\n\
Accept-Language: en, pt-br;q=0.9,*;q=0.8\n\
Allow: GET, POST, PUT, DELETE\n",
		msg);
}

void	send_msg_error(t_connection *conn, int HTTP_code, char *msg)
{
	char	*_msg;

	_msg = (char *)calloc(20 + strlen(msg), sizeof(char));
	sprintf(_msg, "{ \"error\": \"%s\" }", msg);
	send_msg(conn, HTTP_code, _msg);
	free(_msg);
}

void	send_msg_ok(t_connection *conn, int HTTP_code, char *msg)
{
	char	*_msg;

	_msg = (char *)calloc(20 + strlen(msg), sizeof(char));
	sprintf(_msg, "{ \"ok\": \"%s\" }", msg);
	send_msg(conn, HTTP_code, _msg);
	free(_msg);
}
