#include <mongoc.h>
#include "request.h"

static char	check_token_expires(bson_t *user);
static bson_t	*check_token_exists(char *token);
static char	*get_token_of_header(t_request *req);
static char	valid_format_token(t_connection *conn, char *raw, char **token_ptr);

char	auth_middleware(t_connection *conn, t_request *req)
{
	char	*raw;
	bson_t	*user;
	char	*token;

	if (!(raw  = get_token_of_header(req)))
	{
		free(raw);
		send_msg_error(conn, HTTP_BAD, "Token not found.");
		return (EXIT_FAILURE);
	}

	if (valid_format_token(conn, raw, &token) == EXIT_FAILURE)
	{
		free(raw);
		return (EXIT_FAILURE);
	}

	if (!(user = check_token_exists(token)))
	{
		free(raw);
		bson_destroy(user);
		send_msg_error(conn, HTTP_BAD, "Invalid token.");
		return (EXIT_FAILURE);
	}

	if (check_token_expires(user) == EXIT_FAILURE)
	{
		free(raw);
		bson_destroy(user);
		send_msg_error(conn, HTTP_BAD, "Token expires.");
		return (EXIT_FAILURE);
	}

	req->id = digest_token((const u_int8_t *)token);

	free(raw);
	bson_destroy(user);
	if (!bson_oid_is_valid(req->id, strlen(req->id)))
	{
		free(req->id);
		send_msg_error(conn, HTTP_BAD, "Invalid id token.");
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}

static char	*get_token_of_header(t_request *req)
{
	struct mg_str	*token;

	token = mg_http_get_header(req, "Authorization");

	if (!token)
		return (NULL);
	return (strndup(token->ptr, token->len));
}

static char	valid_format_token(t_connection *conn, char *raw, char **token_ptr)
{
	char	*token;
	char	*bearer;

	bearer = strstr(raw, "Bearer ");

	if (!bearer)
	{
		send_msg_error(conn, HTTP_BAD, "Token mal formated.");
		return (EXIT_FAILURE);
	}

	token = bearer + strlen("Bearer ");

	if (strlen(token) < 60 || strlen(token) > 200)
	{
		send_msg_error(conn, HTTP_BAD, "Token mal formated.");
		return (EXIT_FAILURE);
	}

	if (!(exec_regex("^([0-9a-fA-F]{2})*$", token)))
	{
		send_msg_error(conn, HTTP_BAD, "Token mal formated.");
		return (EXIT_FAILURE);
	}

	(*token_ptr) = token;
	return (EXIT_SUCCESS);
}

static bson_t	*check_token_exists(char *token)
{
	bson_t			*user;
	bson_t			*query;
	t_collection	*collection;

	query = bson_new();
	BSON_APPEND_UTF8(query, "token", token);
	collection = mongoc_database_get_collection(get_instance_database()->database, "user");
	if (!(user = db_select("user", query, NULL)))
	{
		bson_destroy(user);
		bson_destroy(query);
		mongoc_collection_destroy(collection);
		return (NULL);
	}

	bson_destroy(query);
	mongoc_collection_destroy(collection);
	return (user);
}

static char	check_token_expires(bson_t *user)
{
	bson_iter_t		iter;
	bson_iter_t		sub_iter;

	if (!bson_iter_init(&iter, user))
		return (EXIT_FAILURE);

	if (!bson_iter_find_descendant(&iter, "user._token_expires_as", &sub_iter))
		return (EXIT_FAILURE);

	if (now() >= bson_iter_date_time(&sub_iter))
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
