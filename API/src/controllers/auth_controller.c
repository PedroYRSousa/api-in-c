#include <time.h>
#include <mongoc.h>
#include "utils.h"
#include "models/auth_model.h"
#include "models/user_model.h"

static time_t	get_time_for_expire(void);
static char	*get_id(bson_t *body, bson_oid_t **iod);
static bson_t	*select_user(t_connection *conn, bson_t *body);
static bson_t	*update_user_get_doc_token(t_connection *conn, char *token, bson_oid_t *oid);

void	auth_user(t_connection *conn, t_request *req)
{
	bson_oid_t		*oid;
	bson_t			*body;
	bson_t			*user;
	char			*token;
	bson_t			*doc_token;

	if (!(body = valid_body(conn, req, get_value_user, valid_auth)))
		goto free_invalid_body;

	if (!(user = select_user(conn, body)))
		goto free_invalid_credentials;

	token = get_token((const u_int8_t *)get_id(user, &oid));

	if (!(doc_token = update_user_get_doc_token(conn, token, oid)))
		goto free_not_insert;

	send_result(conn, doc_token, "auth", HTTP_OK);

	free_not_insert:
		free(token);
		bson_destroy(doc_token);

	free_invalid_credentials:
		bson_destroy(user);
		
	free_invalid_body:
		bson_destroy(body);
}

static char	*get_id(bson_t *body, bson_oid_t **iod)
{
	bson_iter_t 		iter;
	static char			id[26];
	bson_iter_t 		sub_iter;

	if (bson_iter_init (&iter, body)) {
		bson_iter_find_descendant(&iter, "user._id" ,&sub_iter);
		(*iod) = (bson_oid_t *)bson_iter_oid(&sub_iter);
		bson_oid_to_string((const bson_oid_t *)(*iod), id);
	}
	return (id);
}

static time_t	get_time_for_expire(void)
{
	const time_t	one_day = (1000 * 60 * 60 * 24);

	return (now() + one_day);
}

static bson_t	*select_user(t_connection *conn, bson_t *body)
{
	bson_t			*user;
	t_collection	*collection;

	collection = mongoc_database_get_collection(get_instance_database()->database, "user");
	if (!(user = db_select("user", body, NULL)))
	{
		bson_destroy(user);
		mongoc_collection_destroy(collection);
		send_msg_error(conn, HTTP_UNAUTHORIZED, "Invalid credentials.");
		return (NULL);
	}

	mongoc_collection_destroy(collection);
	return (user);
}

static bson_t	*update_user_get_doc_token(t_connection *conn, char *token, bson_oid_t *oid)
{
	t_bson_error	error;
	bson_t			*query;
	bson_t			*update;
	bson_t			*doc_token;
	t_collection	*collection;

	query = bson_new();
	update = bson_new();
	BSON_APPEND_OID(query, "_id", oid);
	doc_token = bson_new();
	BSON_APPEND_UTF8(doc_token, "token", token);
	BSON_APPEND_DATE_TIME(doc_token, "_token_expires_as", get_time_for_expire());
	BSON_APPEND_DOCUMENT(update, "$set", doc_token);
	collection = mongoc_database_get_collection(get_instance_database()->database, "user");
	if (!mongoc_collection_update_one(collection, query, update, NULL, NULL, &error))
		send_msg_error(conn, HTTP_BAD, "Internal error.");

	mongoc_collection_destroy(collection);
	bson_destroy(query);
	bson_destroy(update);

	BSON_APPEND_OID(doc_token, "_id", oid);

	return (doc_token);
}
