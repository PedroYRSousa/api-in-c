#ifndef REQUEST_H
# define REQUEST_H

# include "utils.h"

# ifndef METHOD_GET
#  define METHOD_GET 00
# endif

# ifndef METHOD_POST
#  define METHOD_POST 01
# endif

# ifndef METHOD_PUT
#  define METHOD_PUT 02
# endif

# ifndef METHOD_DELETE
#  define METHOD_DELETE 03
# endif

# ifndef METHOD_NULL
#  define METHOD_NULL 04
# endif

int		get_method(t_request *req);

#endif