#include "utils.h"

bson_t	*get_query_id(t_request *req, const char *garbage, char **id_prt, size_t *id_len)
{
	bson_oid_t	oid;
	bson_t		*query;
	size_t		size_garbage;

	size_garbage = strlen(garbage) + 1;
	(*id_prt) = (char *)(req->uri.ptr + size_garbage);
	(*id_len) = req->uri.len - size_garbage;

	query = bson_new();
	bson_oid_init_from_string(&oid, (*id_prt));
	BSON_APPEND_OID(query, "_id", &oid);

	if (!bson_oid_is_valid((*id_prt), (*id_len)))
	{
		bson_destroy(query);
		return (NULL);
	}
	return (query);
}
