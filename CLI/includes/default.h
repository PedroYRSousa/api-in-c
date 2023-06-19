#ifndef DEFAULT_H
# define DEFAULT_H

# include "request.h"

# ifndef SIZE
#  define SIZE 40
# endif

typedef struct s_digest_method
{
	size_t count;
} t_digest_method;

typedef struct s_digest_deafult
{
	t_string uri;
	t_digest_method get;
	t_digest_method put;
	t_digest_method post;
	t_digest_method delete;
	t_digest_method others;
	struct s_digest_deafult *next;
} t_digest_deafult;


void				show_default_row(char *col);
void				show_default(t_request *root);
t_digest_deafult	*digest_default_request(t_request *root);
void				clear_digest_deafult(t_digest_deafult **root);
t_digest_deafult	*digest_default(t_request *req, t_request *root);
char				digest_contains(t_string ref, t_digest_deafult *root);
void				show_default_colunm(char *coll_1, char *coll_2, char *coll_3);
void				add_digest_default(t_digest_deafult *node, t_digest_deafult **root);
void				show_default_method(char *method, t_digest_deafult *digest, int color);

#endif