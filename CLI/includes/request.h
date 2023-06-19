#ifndef REQUEST_H
# define REQUEST_H

typedef struct s_string
{
	char			*ptr;
	unsigned long	size;
}	t_string;

typedef struct s_raw_data
{
	const char	*data;
	t_string	uri;
	t_string	proto;
	t_string	method;
	t_string	status;
	t_string	user_ip;
	t_string	size_res;
	t_string	use_agent;
	t_string	date_time;
	t_string	time_response;
}	t_raw_data;

typedef struct s_request
{
	t_raw_data			raw;
	struct s_request	*next;
}	t_request;

t_request	*get_request(char **file);
t_request	*create_request(char *raw);
void		clear_request(t_request **root);
void		load_requests(char *file, t_request **root);
void		add_request(t_request *req, t_request **root);

#endif