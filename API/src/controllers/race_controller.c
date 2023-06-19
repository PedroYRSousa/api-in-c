#include "utils.h"

void	list_race(t_connection *conn, t_request *req)
{
	t_database		*db;
	bson_t			*race;
	bson_t			*races;
	bson_t			*query;
	mongoc_cursor_t	*cursor;
	t_collection	*collection;

	(void)req;

	query = bson_new();
	db = get_instance_database();
	collection = mongoc_database_get_collection(db->database, "race");
	cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);
	races = bson_new();
	while (mongoc_cursor_next(cursor, (const bson_t **)&race))	{
		BSON_APPEND_DOCUMENT(races, "race", race);
	}

	send_result(conn, races, "race", HTTP_OK);

	bson_destroy(race);
	bson_destroy(races);
	bson_destroy(query);
	mongoc_cursor_destroy(cursor);
	mongoc_collection_destroy(collection);
}

void	get_race(t_connection *conn, t_request *req)
{
	t_database		*db;
	bson_t			*race;
	bson_t			*query;
	size_t			id_len;
	char			*id_ptr;
	t_collection	*collection;

	if (!(query = get_query_id(req, "/race", &id_ptr, &id_len)))
	{
		send_msg_error(conn, HTTP_BAD, "Invalid id.");
		goto free_id_invalid;
	}

	db = get_instance_database();
	collection = mongoc_database_get_collection(db->database, "race");
	if (!(race = db_select("race", query, NULL)))
	{
		send_msg_error(conn, HTTP_NOT_FOUND, "Race not found.");
		goto free_not_found;
	}

	send_result(conn, race, "race", HTTP_OK);

	free_not_found:
	bson_destroy(race);
	mongoc_collection_destroy(collection);

	free_id_invalid:
	bson_destroy(query);
}
