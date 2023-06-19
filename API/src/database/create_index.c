#include <mongoc.h>
#include "database.h"

static char		create_index_user(void);
static char		exec_command(bson_t *command);
static bson_t	*generate_doc(char *target, char unique);

char	create_index(void)
{
	if (!create_index_user())
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static char	create_index_user(void)
{
	bson_t			*command;
	bson_t			*doc_email;
	bson_t			*doc_username;
	bson_t			*doc_password;

	doc_email = generate_doc("email", 1);
	doc_username = generate_doc("username", 1);
	doc_password = generate_doc("password", 0);
	command = BCON_NEW("createIndexes", BCON_UTF8("user"), "indexes", "[",
		BCON_DOCUMENT(doc_username), BCON_DOCUMENT(doc_email), BCON_DOCUMENT(doc_password),
	"]");

	bson_destroy(doc_email);
	bson_destroy(doc_username);
	bson_destroy(doc_password);

	return (exec_command(command));
}

static char	exec_command(bson_t *command)
{
	t_database		*db;
	t_bson_error	error;
	
	db = get_instance_database();
	if (!mongoc_database_write_command_with_opts(db->database, command, NULL, NULL, &error))
	{
		fprintf (stderr, "Error in create indexes: %s\n", error.message);
		bson_destroy(command);
		return (EXIT_FAILURE);
	}

	bson_destroy(command);
	return (EXIT_SUCCESS);
}

static bson_t	*generate_doc(char *target, char unique)
{
	bson_t	*doc;

	doc = BCON_NEW("key","{",
			BCON_UTF8(target), BCON_INT32(1),
		"}",
		"name", BCON_UTF8(target),
		"unique", BCON_BOOL(unique)
	);
	return (doc);
}
