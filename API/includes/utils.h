#ifndef UTILS_H
# define UTILS_H

# ifndef HTTP_OK
#  define HTTP_OK 200
# endif

# ifndef HTTP_CREATE
#  define HTTP_CREATE 201
# endif

# ifndef HTTP_BAD
#  define HTTP_BAD 400
# endif

# ifndef HTTP_UNAUTHORIZED
#  define HTTP_UNAUTHORIZED 401
# endif

# ifndef HTTP_NOT_FOUND
#  define HTTP_NOT_FOUND 404
# endif

# ifndef HTTP_METHOD_FOUND
#  define HTTP_METHOD_FOUND 501
# endif

# ifndef HASH_SIZE
#  define HASH_SIZE 128
# endif

# ifndef IT_MISSING
#  define IT_MISSING 0
# endif

# ifndef IS_OK
#  define IS_OK 1
# endif

# ifndef IS_DUPLICATE
#  define IS_DUPLICATE -1
# endif

# ifndef IS_INVALID
#  define IS_INVALID -2
# endif

# ifndef SIZE_ID
#  define SIZE_ID 24
# endif

# ifndef SIZE_KEY
#  define SIZE_KEY 129
# endif

# include "mongoose.h"
# include "database.h"
# include <mongoc/mongoc.h>

typedef struct mg_http_message	t_request;
typedef struct mg_mgr			t_mg_server;
typedef struct mg_connection	t_connection;

// Mensage
void	send_msg(t_connection *conn, int HTTP_code, char *msg);
void	send_msg_ok(t_connection *conn, int HTTP_code, char *msg);
void	send_msg_error(t_connection *conn, int HTTP_code, char *msg);

// Request
bson_t	*get_query_id(t_request *req, const char *garbage, char **id_prt, size_t *id_len);
bson_t	*get_body(t_connection *conn, t_request *req, void (*get_value)(bson_t, bson_t *));

// Security
char	*get_token(const u_int8_t *id);
char	*digest_token(const u_int8_t *token);
void 	get_hash(char *src, char hash[HASH_SIZE + 1]);

// Parse
void	strhex_to_str(const u_int8_t *src, char *dest);
void	str_to_strhex(const unsigned char *src, char *dest);
char	json_to_bson(bson_t *doc, const char *json, size_t len);

// Validators
bool	is_valid_email(char *email);
bool	is_valid_username(char *username);
bool	exec_regex(const char *expression, char *target);

// Controllers
void	send_result(t_connection *conn, bson_t *doc, char *name, int HTTP_code);
bson_t	*valid_body(t_connection *conn, t_request *req, void (*get_value)(bson_t, bson_t *), char *(*valid)(bson_t *));

// Time
time_t	now(void);

#endif