#ifndef DATABASE_H
# define DATABASE_H

#ifndef DATABASE_NAME
# define DATABASE_NAME "42rolls"
#endif

#include "utils.h"
#include <mongoc/mongoc.h>

typedef mongoc_uri_t		t_uri;
typedef mongoc_client_t		t_client;
typedef mongoc_collection_t	t_collection;
typedef bson_error_t		t_bson_error;
typedef mongoc_database_t	t_mongo_database;

typedef struct	s_database
{
	t_client			*client;
	t_mongo_database	*database;
}	t_database;

char		create_index(void);
char		connect_database(void);
void		disconnect_database(void);
t_database	*get_instance_database(void);
bson_t		*db_select(const char *name, const bson_t *query, const bson_t *opts);
char		db_insert(struct mg_connection *conn, const bson_t *doc, const char *collection_name);

#endif