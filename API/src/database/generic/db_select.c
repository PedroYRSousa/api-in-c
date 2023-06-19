#include "database.h"

bson_t	*db_select(const char *name, const bson_t *query, const bson_t *opts)
{
	t_database		*db;
	const bson_t	*doc;
	bson_t			*output;
	mongoc_cursor_t	*cursor;
	t_collection	*collection;

	output = bson_new();

	db = get_instance_database();
	collection = mongoc_database_get_collection(db->database, name);
	cursor = mongoc_collection_find_with_opts(collection, query, opts, NULL);
	while (mongoc_cursor_next(cursor, &doc))
	{
		bson_append_document(output, name, strlen(name), (bson_t *)doc);
		bson_destroy((bson_t *)doc);
	}

	mongoc_cursor_destroy(cursor);
	mongoc_collection_destroy(collection);
	
	if (((output->len - 5) == 0))
	{
		bson_destroy(output);
		return (NULL);
	}
	return (output);
}
