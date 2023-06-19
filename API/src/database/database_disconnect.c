#include "database.h"

void	disconnect_database(void)
{
	t_database	*db;

	db = get_instance_database();
	mongoc_database_destroy(db->database);
	mongoc_client_destroy(db->client);
	mongoc_cleanup();
}
