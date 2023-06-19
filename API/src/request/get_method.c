#include <mongoc.h>
#include "request.h"

static char	is_get(t_request *req);
static char	is_post(t_request *req);
static char	is_put(t_request *req);
static char	is_delete(t_request *req);

int	get_method(t_request *req)
{
	if (is_get(req))
		return (METHOD_GET);
	if (is_post(req))
		return (METHOD_POST);
	if (is_put(req))
		return (METHOD_PUT);
	if (is_delete(req))
		return (METHOD_DELETE);
	else
		return (METHOD_NULL);
}

static char	is_get(t_request *req)
{
	return (strncmp("GET", req->method.ptr, req->method.len) == 0);
}

static char	is_post(t_request *req)
{
	return (strncmp("POST", req->method.ptr, req->method.len) == 0);
}

static char	is_put(t_request *req)
{
	return (strncmp("PUT", req->method.ptr, req->method.len) == 0);
}

static char	is_delete(t_request *req)
{
	return (strncmp("DELETE", req->method.ptr, req->method.len) == 0);
}