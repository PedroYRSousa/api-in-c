#include "request.h"
#include <stdlib.h>
#include <string.h>

t_request	*create_request(char *raw)
{
	t_request	*req;

	req = (t_request *)calloc(1, sizeof(t_request));
	req->raw.data = raw;

	req->raw.user_ip.ptr = raw;
	req->raw.user_ip.size = (strstr(raw, " ") - raw);

	req->raw.date_time.ptr = (req->raw.user_ip.ptr + req->raw.user_ip.size + 2);
	req->raw.date_time.size = (strstr(req->raw.date_time.ptr, "]") - req->raw.date_time.ptr);

	req->raw.method.ptr = (req->raw.date_time.ptr + req->raw.date_time.size + 3);
	req->raw.method.size = (strstr(req->raw.method.ptr, " ") - req->raw.method.ptr);
	
	req->raw.uri.ptr = (req->raw.method.ptr + req->raw.method.size + 1);
	req->raw.uri.size = (strstr(req->raw.uri.ptr, " ") - req->raw.uri.ptr);

	req->raw.proto.ptr = (req->raw.uri.ptr + req->raw.uri.size + 1);
	req->raw.proto.size = (strstr(req->raw.proto.ptr, "\"") - req->raw.proto.ptr);

	req->raw.status.ptr = (req->raw.proto.ptr + req->raw.proto.size + 2);
	req->raw.status.size = (strstr(req->raw.status.ptr, " ") - req->raw.status.ptr);

	req->raw.size_res.ptr = (req->raw.status.ptr + req->raw.status.size + 1);
	req->raw.size_res.size = (strstr(req->raw.size_res.ptr, " ") - req->raw.size_res.ptr);

	req->raw.use_agent.ptr = (req->raw.size_res.ptr + req->raw.size_res.size + 1);
	req->raw.use_agent.size = (strstr(req->raw.use_agent.ptr, " - - ") - req->raw.use_agent.ptr);

	req->raw.time_response.ptr = (req->raw.use_agent.ptr + req->raw.use_agent.size + 5);
	req->raw.time_response.size = (strstr(req->raw.time_response.ptr, "\n") - req->raw.time_response.ptr);
	
	return (req);
}
