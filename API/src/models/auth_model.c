#include <mongoc.h>
#include "utils.h"

char	*valid_auth(bson_t *user)
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

	if (username == IT_MISSING && email == IT_MISSING)
		return ("'email' and/or 'username' is required.");

	if (email != IS_OK && email != IT_MISSING)
		return((email == IS_INVALID) ? ("'email' is invalid.") : ("'email' is duplicated."));
	if (username != IS_OK && username != IT_MISSING)
		return((username == IS_INVALID) ? ("'username' is invalid.") : ("'username' is duplicated."));
	if (password != IS_OK)
		return((password == IT_MISSING) ? ("'password' is required.") : ("'password' is duplicated."));

	return (NULL);
}
