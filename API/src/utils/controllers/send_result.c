#include <mongoc.h>
#include "utils.h"

static bson_t	*clear_body_user(bson_t *body);

void send_result(t_connection *conn, bson_t *doc, char *name, int HTTP_code)
{
	char	is_freeable = true;
	char	*body_response_json;
	bson_t	*body_response = NULL;

	is_freeable = false;
	body_response = doc;

	if (strcmp(name, "user") == 0)
	{
		is_freeable = true;
		body_response = clear_body_user(doc);
	}

	body_response_json = bson_as_canonical_extended_json(body_response, NULL);
	send_msg(conn, HTTP_code, body_response_json);

	if (is_freeable)
		bson_free(body_response);
	bson_free(body_response_json);
}

static bson_t	*clear_body_user(bson_t *body)
{
	bson_iter_t	iter;
	bson_iter_t	sub_iter;
	bson_t		*body_cleaned;
	
	body_cleaned = bson_new();
	if (bson_iter_init (&iter, body)) {
		if (bson_iter_next(&iter))
		{
			bson_iter_recurse(&iter, &sub_iter);
			while (bson_iter_next(&sub_iter))
			{
				if (strcmp(bson_iter_key(&sub_iter), "username") == 0)
					BSON_APPEND_UTF8(body_cleaned, bson_iter_key(&sub_iter), bson_iter_utf8(&sub_iter, NULL));
				if (strcmp(bson_iter_key(&sub_iter), "email") == 0)
					BSON_APPEND_UTF8(body_cleaned, bson_iter_key(&sub_iter), bson_iter_utf8(&sub_iter, NULL));
			}
		}
		
	}
	return (body_cleaned);
}
