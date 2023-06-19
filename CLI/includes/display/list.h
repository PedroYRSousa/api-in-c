#ifndef LIST_H
# define LIST_H

# include "config.h"
# include "request.h"

typedef t_request t_list;

void	clear_list(t_list	**list);
t_list	*init_list(t_config config, t_request *requests);

#endif