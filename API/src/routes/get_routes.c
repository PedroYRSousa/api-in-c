#include "routes.h"
#include "request.h"
#include "controllers/auth_controller.h"
#include "controllers/user_controller.h"
#include "controllers/race_controller.h"
#include "controllers/roll_controller.h"
#include "controllers/class_controller.h"
#include "middlewares/auth_middleware.h"

static void	route_root(t_connection *conn, t_request *req);
static void	route_auth(t_connection *conn, t_request *req);
static void	route_user(t_connection *conn, t_request *req);
static void	route_roll(t_connection *conn, t_request *req);
static void	route_race(t_connection *conn, t_request *req);
static void	route_class(t_connection *conn, t_request *req);
static void	route_not_found(t_connection *conn, t_request *req);

void	get_routes(t_request *req, void (**route)(t_connection *, t_request *))
{
	if (mg_http_match_uri(req, "/"))
		(*route) = route_root;
	else if (mg_http_match_uri(req, "/auth"))
		(*route) = route_auth;
	else if (mg_http_match_uri(req, "/user") || mg_http_match_uri(req, "/user/*"))
		(*route) = route_user;
	else if (mg_http_match_uri(req, "/roll") || mg_http_match_uri(req, "/roll/*"))
		(*route) = route_roll;
	else if (mg_http_match_uri(req, "/class") || mg_http_match_uri(req, "/class/*"))
		(*route) = route_class;
	else if (mg_http_match_uri(req, "/race") || mg_http_match_uri(req, "/race/*"))
		(*route) = route_race;
	else
		(*route) = route_not_found;
}

static void	route_root(t_connection *conn, t_request *req)
{
	char	*json;
	bson_t	*output = NULL;

	(void)req;
	if ((get_method(req) == METHOD_GET))
	{
		output = BCON_NEW(
				"Info", "{",
					"Author", "Pedro Yago Rabelo de Sousa",
					"Version", "0.0.0.1 Alpha",
					"Date", "26/02/2022",
					"Description", "REST API made for 42Labs.",
				"}");
		json = bson_as_canonical_extended_json(output, NULL);
		send_msg(conn, HTTP_OK, json);
		bson_destroy(output);
		free(json);
	}
	else
		send_msg(conn, HTTP_METHOD_FOUND, "");
}

static void	route_not_found(t_connection *conn, t_request *req)
{
	(void)req;
	send_msg(conn, HTTP_NOT_FOUND, "");
}

static void	route_auth(t_connection *conn, t_request *req)
{
	if ((get_method(req) == METHOD_POST))
		auth_user(conn, req);
	else
		send_msg(conn, HTTP_METHOD_FOUND, "");
}

static void	route_user(t_connection *conn, t_request *req)
{
	if ((get_method(req) == METHOD_GET))
	{
		if(auth_middleware(conn, req) == EXIT_SUCCESS)
			get_user(conn, req);
	}
	else if ((get_method(req) == METHOD_PUT) && (mg_http_match_uri(req, "/user/*")))
	{
		if(auth_middleware(conn, req) == EXIT_SUCCESS)
			update_user(conn, req);
	}
	else if ((get_method(req) == METHOD_DELETE) && (mg_http_match_uri(req, "/user/*")))
	{
		if(auth_middleware(conn, req) == EXIT_SUCCESS)
			delete_user(conn, req);
	}
	else if ((get_method(req) == METHOD_POST && (mg_http_match_uri(req, "/user"))))
			create_user(conn, req);
	else
		send_msg(conn, HTTP_METHOD_FOUND, "");

	if (req->id)
		free(req->id);
}

static void	route_roll(t_connection *conn, t_request *req)
{
	if ((get_method(req) == METHOD_GET) && (mg_http_match_uri(req, "/roll")))
	{
		if(auth_middleware(conn, req) == EXIT_SUCCESS)
			list_roll(conn, req);
	}
	else if ((get_method(req) == METHOD_GET) && (mg_http_match_uri(req, "/roll/*")))
	{
		if(auth_middleware(conn, req) == EXIT_SUCCESS)
			get_roll(conn, req);
	}
	else if ((get_method(req) == METHOD_DELETE))
	{
		if(auth_middleware(conn, req) == EXIT_SUCCESS)
			delete_roll(conn, req);
	}
	else if ((get_method(req) == METHOD_POST))
	{
		if(auth_middleware(conn, req) == EXIT_SUCCESS)
			create_roll(conn, req);
	}
	else
		send_msg(conn, HTTP_METHOD_FOUND, "");

	if (req->id)
		free(req->id);
}

static void	route_class(t_connection *conn, t_request *req)
{
	if ((get_method(req) == METHOD_GET) && (mg_http_match_uri(req, "/class")))
		list_class(conn, req);
	else if ((get_method(req) == METHOD_GET) && (mg_http_match_uri(req, "/class/*")))
		get_class(conn, req);
	else
		send_msg(conn, HTTP_METHOD_FOUND, "");
}

static void	route_race(t_connection *conn, t_request *req)
{
	if ((get_method(req) == METHOD_GET) && (mg_http_match_uri(req, "/race")))
		list_race(conn, req);
	else if ((get_method(req) == METHOD_GET) && (mg_http_match_uri(req, "/race/*")))
		get_race(conn, req);
	else
		send_msg(conn, HTTP_METHOD_FOUND, "");
}
