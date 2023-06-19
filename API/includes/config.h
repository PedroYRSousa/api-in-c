#ifndef CONFIG_H
# define CONFIG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef	struct s_string
{
	char			*ptr;
	unsigned long	size;
}	t_string;

typedef struct s_config
{
	t_string	secret;
	t_string	log_path;
	char		*file_raw;
	t_string	host_server;
	t_string	host_database;
}	t_config;

char		load_config(void);
void		clear_config(void);
t_config	*get_instance_config(void);

#endif