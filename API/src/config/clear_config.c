#include <stdlib.h>
#include "config.h"

void	clear_config(void)
{
	t_config	*config;

	config = get_instance_config();
	free(config->file_raw);
}
