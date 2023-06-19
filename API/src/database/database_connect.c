#include "utils.h"
#include "config.h"

char	connect_database(void)
{
	t_database		*db;
	t_uri			*uri;
	t_bson_error	error;
	t_config		config;

	config = (*get_instance_config());
	mongoc_init();

	db = get_instance_database();
	uri = mongoc_uri_new_with_error(config.host_database.ptr, &error);
	if (!uri)
	{
		fprintf(stderr,
				"failed to parse URI: %s\n"
				"error message:       %s\n",
				config.host_database.ptr,
				error.message);
		return (EXIT_FAILURE);
	}

	db->client = mongoc_client_new_from_uri(uri);
	mongoc_uri_destroy(uri);
	if (!(db->client))
		return (EXIT_FAILURE);

	mongoc_client_set_appname(db->client , "API");

	db->database = mongoc_client_get_database(db->client, DATABASE_NAME);

	if (!create_index())
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}	
