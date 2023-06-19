#include <mongoc.h>
#include "utils.h"

static char	is_valid_key(bson_iter_t iter);

char	*valid_user_update(bson_t	*user)
{
	bson_iter_t		iter;
	char			email = 0;
	char			username = 0;
	char			password = 0;

	if (!bson_iter_init(&iter, user))
		return ("Internal error!");

	while (bson_iter_next(&iter))
	{
		if (strcmp(bson_iter_key(&iter), "email") == 0)
		{
			email = (email == 0) ? IS_OK :  IS_DUPLICATE;
			if (email == IS_OK && !is_valid_email((char *)bson_iter_utf8(&iter, NULL)))
				email = IS_INVALID;
		}
		else if (strcmp(bson_iter_key(&iter), "username") == 0)
		{
			username = (username == 0) ? IS_OK :  IS_DUPLICATE;
			if (username == IS_OK && !is_valid_username((char *)bson_iter_utf8(&iter, NULL)))
				username = IS_INVALID;
		}
		else if (strcmp(bson_iter_key(&iter), "password") == 0)
			password = (password == 0) ? IS_OK :  IS_DUPLICATE;
	}

	if (email != IS_OK)
		return((email == IT_MISSING) ? ("'email' is required.") : (email == IS_INVALID) ? ("'email' is invalid.") : ("'email' is duplicated."));
	if (username != IS_OK)
		return((username == IT_MISSING) ? ("'username' is required.") : (username == IS_INVALID) ? ("'username' is invalid.") : ("'username' is duplicated."));
	if (password != IS_OK && password != IT_MISSING)
		return("'password' is duplicated.");

	return (NULL);
}

char	*valid_user(bson_t	*user)
{
	bson_iter_t		iter;
	char			email = 0;
	char			username = 0;
	char			password = 0;

	if (!bson_iter_init(&iter, user))
		return ("Internal error!");

	while (bson_iter_next(&iter))
	{
		if (strcmp(bson_iter_key(&iter), "email") == 0)
		{
			email = (email == 0) ? IS_OK :  IS_DUPLICATE;
			if (email == IS_OK && !is_valid_email((char *)bson_iter_utf8(&iter, NULL)))
				email = IS_INVALID;
		}
		else if (strcmp(bson_iter_key(&iter), "username") == 0)
		{
			username = (username == 0) ? IS_OK :  IS_DUPLICATE;
			if (username == IS_OK && !is_valid_username((char *)bson_iter_utf8(&iter, NULL)))
				username = IS_INVALID;
		}
		else if (strcmp(bson_iter_key(&iter), "password") == 0)
			password = (password == 0) ? IS_OK :  IS_DUPLICATE;
	}

	if (email != IS_OK)
		return((email == IT_MISSING) ? ("'email' is required.") : (email == IS_INVALID) ? ("'email' is invalid.") : ("'email' is duplicated."));
	if (username != IS_OK)
		return((username == IT_MISSING) ? ("'username' is required.") : (username == IS_INVALID) ? ("'username' is invalid.") : ("'username' is duplicated."));
	if (password != IS_OK)
		return((password == IT_MISSING) ? ("'password' is required.") : ("'password' is duplicated."));

	return (NULL);
}

void	get_value_user(bson_t doc, bson_t *user)
{
	bson_iter_t	iter;
	char		*password;
	char		hash[HASH_SIZE + 1];

	if (!bson_iter_init(&iter, &doc))
		return ;

	while (bson_iter_next(&iter))
	{
		if (!is_valid_key(iter))
			continue;
		if (strcmp(bson_iter_key(&iter), "password") == 0)
			{
				password = bson_iter_dup_utf8(&iter, NULL);
				get_hash(password, hash);
				BSON_APPEND_UTF8(user, "password", hash);
				free(password);
			}
		else
			bson_append_iter(user, bson_iter_key(&iter), strlen(bson_iter_key(&iter)), &iter);
	}
}

static char	is_valid_key(bson_iter_t iter)
{
	return (strcmp(bson_iter_key(&iter), "username") == 0
		|| strcmp(bson_iter_key(&iter), "password")
		|| strcmp(bson_iter_key(&iter), "email"));
}
