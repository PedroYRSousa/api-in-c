#include "database.h"

char	db_insert(struct mg_connection *conn, const bson_t *doc, const char *collection_name)
{
	t_database		*db;
	t_bson_error	error;
	t_collection	*collection;

	(void)conn;
	db = get_instance_database();
	collection = mongoc_database_get_collection(db->database, collection_name);
	if (!mongoc_collection_insert_one(collection, doc, NULL, NULL, &error))
	{
		mongoc_collection_destroy(collection);
		return (false);
	}
	mongoc_collection_destroy(collection);
	return (true);
}
