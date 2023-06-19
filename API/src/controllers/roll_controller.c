#include <mongoc.h>
#include "utils.h"

char	is_my(bson_t *roll, char *id)
{
	bson_iter_t	iter;
	bson_iter_t	sub_iter;

	if (bson_iter_init(&iter, roll))
	{
		bson_iter_next(&iter);
		bson_iter_recurse(&iter, &sub_iter);
		if (bson_iter_find(&sub_iter, "userId"))
		{
			if (strcmp(id, bson_iter_utf8(&sub_iter, NULL)))
				return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

void	list_roll(t_connection *conn, t_request *req)
{
	t_database		*db;
	bson_t			*roll;
	bson_t			*rolls;
	bson_t			*query;
	mongoc_cursor_t	*cursor;
	t_collection	*collection;

	if (!req->id)
	{
		send_msg_error(conn, HTTP_UNAUTHORIZED, "Not authorized!");
		return ;
	}

	query = bson_new();
	BSON_APPEND_UTF8(query, "userId", req->id);

	db = get_instance_database();
	collection = mongoc_database_get_collection(db->database, "roll");
	cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);
	rolls = bson_new();
	while (mongoc_cursor_next(cursor, (const bson_t **)&roll))	{
		BSON_APPEND_DOCUMENT(rolls, "roll", roll);
	}

	send_result(conn, rolls, "roll", HTTP_OK);

	bson_destroy(roll);
	bson_destroy(rolls);
	bson_destroy(query);
	mongoc_cursor_destroy(cursor);
	mongoc_collection_destroy(collection);
}

void	get_roll(t_connection *conn, t_request *req)
{
	t_database		*db;
	bson_t			*roll;
	bson_t			*query;
	size_t			id_len;
	char			*id_ptr;
	t_collection	*collection;

	if (!req->id)
	{
		send_msg_error(conn, HTTP_UNAUTHORIZED, "Not authorized!");
		return ;
	}

	if (!(query = get_query_id(req, "/roll", &id_ptr, &id_len)))
	{
		send_msg_error(conn, HTTP_BAD, "Invalid id.");
		goto free_id_invalid;
	}

	db = get_instance_database();
	collection = mongoc_database_get_collection(db->database, "roll");
	if (!(roll = db_select("roll", query, NULL)))
	{
		send_msg_error(conn, HTTP_NOT_FOUND, "Roll not found.");
		goto free_not_found;
	}

	if (!is_my(roll, req->id))
	{
		send_msg_error(conn, HTTP_UNAUTHORIZED, "Not authorized!");
		goto free_is_not_my;
	}

	send_result(conn, roll, "roll", HTTP_OK);

	free_is_not_my:

	free_not_found:
		bson_destroy(roll);
		mongoc_collection_destroy(collection);

	free_id_invalid:
		bson_destroy(query);
}

void	create_roll(t_connection *conn, t_request *req)
{
	int				dice;
	char			*dice_prt;
	int				size_garbage;
	bson_t			*body_response;

	if (!req->id)
	{
		send_msg_error(conn, HTTP_UNAUTHORIZED, "Not authorized!");
		return ;
	}
	
	size_garbage = strlen("/roll/");
	dice_prt = (char *)(req->uri.ptr + size_garbage);

	if ((dice = atoi(dice_prt)) == 0)
	{
		send_msg_error(conn, HTTP_UNAUTHORIZED, "Invalid input!");
		return ;
	}

	if (dice != 4 && dice != 6 && dice != 8 && dice != 10 && dice != 20 && dice != 100)
	{
		send_msg_error(conn, HTTP_UNAUTHORIZED, "Invalid dice!");
		return ;
	}

	int result = (rand() % (dice + 1));
	if (!result)
		result	+= 1; 

	body_response = bson_new();
	BSON_APPEND_DATE_TIME(body_response, "date", now());
	BSON_APPEND_INT32(body_response, "result", result);
	BSON_APPEND_UTF8(body_response, "userId", req->id);

	if (!db_insert(conn, body_response, "roll"))
	{
		send_msg_error(conn, HTTP_BAD, "Internal error.");
		goto free_not_insert;
	}
	
	send_result(conn, body_response, "roll", HTTP_CREATE);

	free_not_insert:
		bson_destroy(body_response);
}

void	delete_roll(t_connection *conn, t_request *req)
{
	t_database		*db;
	t_bson_error	error;
	bson_t			*roll;
	bson_t			*query;
	size_t			id_len;
	char			*id_ptr;
	t_collection	*collection;

	if (!req->id)
	{
		send_msg_error(conn, HTTP_UNAUTHORIZED, "Not authorized!");
		return ;
	}

	if (!(query = get_query_id(req, "/roll", &id_ptr, &id_len)))
	{
		send_msg_error(conn, HTTP_BAD, "Invalid id.");
		goto free_id_invalid;
	}

	db = get_instance_database();
	collection = mongoc_database_get_collection(db->database, "roll");
	if (!(roll = db_select("roll", query, NULL)))
	{
		send_msg_error(conn, HTTP_NOT_FOUND, "Roll not found.");
		goto free_not_found;
	}

	if (!is_my(roll, req->id))
	{
		send_msg_error(conn, HTTP_UNAUTHORIZED, "Not authorized!");
		goto free_is_not_my;
	}

	if (!(mongoc_collection_delete_one(collection, query, NULL, NULL, &error)))
	{
		send_msg_error(conn, HTTP_BAD, "Internal error.");
		goto free_not_delete;
	}
	
	send_msg_ok(conn, HTTP_OK, "Roll deleted!");

	free_not_delete:

	free_is_not_my:

	free_not_found:
		bson_destroy(roll);
		mongoc_collection_destroy(collection);

	free_id_invalid:
		bson_destroy(query);
}