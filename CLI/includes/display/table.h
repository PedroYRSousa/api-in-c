#ifndef TABLE_H
# define TABLE_H

#ifndef	SIZE_TABLE
# define SIZE_TABLE 40 
#endif

# include "list.h"
# include "config.h"
# include "request.h"

typedef struct s_table
{
	t_list			*row;
	unsigned long	count;
	struct s_table	*next;
}	t_table;

t_table	*init_table(t_list *list);
void	clear_table(t_table	**table);

#endif