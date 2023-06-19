#include <mongoc.h>
#include "utils.h"

char	json_to_bson(bson_t *doc, const char *json, size_t len)
{
	t_bson_error error;
	bson_json_reader_t *reader;

	reader = bson_json_data_reader_new(0, len);
	bson_json_data_reader_ingest(reader, (const uint8_t *)json, len);
	if (bson_json_reader_read(reader, doc, &error) < 0)
	{
		bson_json_reader_destroy(reader);
		return (0);
	}
	bson_json_reader_destroy(reader);
	return (1);
}
