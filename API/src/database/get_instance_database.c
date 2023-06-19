#include "database.h"

t_database	*get_instance_database(void)
{
	static t_database	__instance;

	return (&__instance);
}
