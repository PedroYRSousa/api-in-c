#include "utils.h"
#include "models/user_model.h"

void	get_user(t_connection *conn, t_request *req)
{
	t_database		*db;
	bson_t			*user;
	bson_t			*query;
	size_t			id_len;
	char			*id_ptr;
	t_collection	*collection;

	if (!(query = get_query_id(req, "/user", &id_ptr, &id_len)))
	{
		send_msg_error(conn, HTTP_BAD, "Invalid id.");
		goto free_id_invalid;
	}

	if (strncmp(req->id, id_ptr, id_len) != 0)
	{
		send_msg_error(conn, HTTP_UNAUTHORIZED, "Not authorized!");
		goto free_not_authorized;
	}

	db = get_instance_database();
	collection = mongoc_database_get_collection(db->database, "user");
	if (!(user = db_select("user", query, NULL)))
	{
		send_msg_error(conn, HTTP_NOT_FOUND, "User not found.");
		goto free_not_found;
	}

	send_result(conn, user, "user", HTTP_OK);

	free_not_found:
	bson_destroy(user);
	mongoc_collection_destroy(collection);

	free_not_authorized:

	free_id_invalid:
	bson_destroy(query);
}

void	create_user(t_connection *conn, t_request *req)
{
	t_database		*db;
	bson_t			*user;
	t_collection	*collection;
	bson_t			*body_response;

	if (!(user = valid_body(conn, req, get_value_user, valid_user)))
		goto free_not_insert;

	if (!db_insert(conn, user, "user"))
	{
		send_msg_error(conn, HTTP_BAD, "Username or Email already registered.");
		goto free_not_insert;
	}
	
	db = get_instance_database();
	collection = mongoc_database_get_collection(db->database, "user");
	if (!(body_response = db_select("user", user, NULL)))
	{
		send_msg_error(conn, HTTP_NOT_FOUND, "User not found.");
		goto free_not_found;
	}

	send_result(conn, body_response, "user", HTTP_CREATE);

	free_not_found:
		bson_destroy(body_response);
		mongoc_collection_destroy(collection);

	free_not_insert:
		bson_destroy(user);
}

void	update_user(t_connection *conn, t_request *req)
{
	t_database		*db;
	t_bson_error	error;
	bson_t			*opts;
	bson_t			*user;
	bson_t			*query;
	size_t			id_len;
	char			*id_ptr;
	bson_t			*update;
	bson_t			*old_user = NULL;
	t_collection	*collection = NULL;

	opts = BCON_NEW(
		"projection", "{",
			"username", BCON_BOOL (true), 
			"email", BCON_BOOL (true),
		"}");

	if (!(query = get_query_id(req, "/user", &id_ptr, &id_len)))
	{
		send_msg_error(conn, HTTP_BAD, "Invalid id.");
		goto free_id_invalid;
	}

	if (strncmp(req->id, id_ptr, id_len) != 0)
	{
		send_msg_error(conn, HTTP_UNAUTHORIZED, "Not authorized!");
		goto free_not_authorized;
	}

	if (!(user = valid_body(conn, req, get_value_user, valid_user_update)))
		goto free_invalid_body;

	db = get_instance_database();
	collection = mongoc_database_get_collection(db->database, "user");
	if (!(old_user = db_select("user", query, opts)))
		send_msg_error(conn, HTTP_NOT_FOUND, "User not found.");

	update = bson_new();
	BSON_APPEND_DOCUMENT(update, "$set", user);

	if (!mongoc_collection_update_one(collection, query, update, NULL, NULL, &error))
	{
		if (strstr(error.message, "username"))
			send_msg_error(conn, HTTP_BAD, "Username already registered.");
		else if (strstr(error.message, "email"))
			send_msg_error(conn, HTTP_BAD, "E-mail already registered.");
		else
			send_msg_error(conn, HTTP_BAD, "Internal error.");
		goto free_not_insert;
	}

	send_result(conn, user, "user", HTTP_CREATE);

	free_not_insert:
		bson_destroy(update);
	
	free_invalid_body:
		bson_destroy(old_user);
		bson_destroy(user);
		mongoc_collection_destroy(collection);

	free_not_authorized:

	free_id_invalid:
		bson_destroy(opts);
		bson_destroy(query);
}

void	delete_user(t_connection *conn, t_request *req)
{
	t_database		*db;
	bson_t			*user;
	t_bson_error	error;
	bson_t			*query;
	size_t			id_len;
	char			*id_ptr;
	t_collection	*collection;

	if (!(query = get_query_id(req, "/user", &id_ptr, &id_len)))
	{
		send_msg_error(conn, HTTP_BAD, "Invalid id.");
		goto free_id_invalid;
	}

	if (strncmp(req->id, id_ptr, id_len) != 0)
	{
		send_msg_error(conn, HTTP_UNAUTHORIZED, "Not authorized!");
		goto free_not_authorized;
	}

	db = get_instance_database();
	collection = mongoc_database_get_collection(db->database, "user");
	if (!(user = db_select("user", query, NULL)))
	{
		send_msg_error(conn, HTTP_NOT_FOUND, "User not found.");
		goto free_not_found;
	}

	if (!(mongoc_collection_delete_one(collection, query, NULL, NULL, &error)))
	{
		send_msg_error(conn, HTTP_BAD, "Internal error.");
		goto free_not_delete;
	}

	send_msg_ok(conn, HTTP_OK, "User deleted!");

	free_not_delete:

	free_not_found:
		bson_destroy(user);
		mongoc_collection_destroy(collection);

	free_not_authorized:

	free_id_invalid:
		bson_destroy(query);
}