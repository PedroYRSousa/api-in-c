#include "utils.h"

void	list_class(t_connection *conn, t_request *req)
{
	t_database		*db;
	bson_t			*class;
	bson_t			*classes;
	bson_t			*query;
	mongoc_cursor_t	*cursor;
	t_collection	*collection;

	(void)req;

	query = bson_new();
	db = get_instance_database();
	collection = mongoc_database_get_collection(db->database, "class");
	cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);
	classes = bson_new();
	while (mongoc_cursor_next(cursor, (const bson_t **)&class))	{
		BSON_APPEND_DOCUMENT(classes, "class", class);
	}

	send_result(conn, classes, "class", HTTP_OK);

	bson_destroy(class);
	bson_destroy(classes);
	bson_destroy(query);
	mongoc_cursor_destroy(cursor);
	mongoc_collection_destroy(collection);
}

void	get_class(t_connection *conn, t_request *req)
{
	t_database		*db;
	bson_t			*class;
	bson_t			*query;
	size_t			id_len;
	char			*id_ptr;
	t_collection	*collection;

	if (!(query = get_query_id(req, "/class", &id_ptr, &id_len)))
	{
		send_msg_error(conn, HTTP_BAD, "Invalid id.");
		goto free_id_invalid;
	}

	db = get_instance_database();
	collection = mongoc_database_get_collection(db->database, "class");
	if (!(class = db_select("class", query, NULL)))
	{
		send_msg_error(conn, HTTP_NOT_FOUND, "Class not found.");
		goto free_not_found;
	}

	send_result(conn, class, "class", HTTP_OK);

	free_not_found:
	bson_destroy(class);
	mongoc_collection_destroy(collection);

	free_id_invalid:
	bson_destroy(query);
}
