#include "logger.h"

t_logger	*get_instance_logger(void)
{
	static t_logger	__instance;

	return(&__instance);
}
