#include "config.h"

t_config	*get_instance_config(void)
{
	static t_config	__instance;

	return (&__instance);
}
