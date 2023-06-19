#include "display.h"

#include <stdio.h>

void	display_log(t_config config, t_request *requests)
{
	t_list	*list;
	t_table	*table;

	if (!config.is_valid)
		return (show_malformated_msg());
	
	list = init_list(config, requests);

	if (config.method_display == TABLE)
	{
		table = init_table(list);
		display_table(config, table);
		clear_table(&table);
	}
	else
		display_list(config, list);
	clear_list(&list);
}
