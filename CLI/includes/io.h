#ifndef IO_H
# define IO_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 0xFFFF
# endif

# include "request.h"

char	*read_log(int fd);
void	read_file(char *file, t_request **root);

#endif