#ifndef CONFIG_H
# define CONFIG_H

# ifndef VALID
#  define VALID 00
# endif
# ifndef MALF_FORMATED
#  define MALF_FORMATED 01
# endif

# ifndef NOT_COLORED
#  define NOT_COLORED 000
# endif
# ifndef COLORED
#  define COLORED 010
# endif

# ifndef NOT_ORDENED
#  define NOT_ORDENED 0000
# endif
# ifndef ORDENED_ASC
#  define ORDENED_ASC 0100
# endif
# ifndef ORDENED_DEC
#  define ORDENED_DEC 0200
# endif

# ifndef SHOW_ALL
#  define SHOW_ALL 00000
# endif
# ifndef ONLY_GET
#  define ONLY_GET 011000
# endif
# ifndef ONLY_POST
#  define ONLY_POST 0101000
# endif
# ifndef ONLY_PUT
#  define ONLY_PUT 01001000
# endif
# ifndef ONLY_DELETE
#  define ONLY_DELETE 010001000
# endif
# ifndef ONLY_OTHERS
#  define ONLY_OTHERS 0100001000
# endif

# ifndef TABLE
#  define TABLE 00000000000
# endif
# ifndef LIST
#  define LIST 01000000000
# endif

typedef struct	s_config
{
	char	filter;
	char	filter_get;
	char	filter_post;
	char	filter_put;
	char	filter_delete;
	char	filter_others;
	char	is_valid;
	char	is_colored;
	char	is_ordened;
	char	method_display;
}	t_config;

t_config	load_config(char **argv);
void		show_malformated_msg(void);

#endif