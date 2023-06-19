#include "logger.h"

void	complete_logger(void)
{
	t_logger	*logger;

	logger = get_instance_logger();

	while (logger->list)
		write_logger(SIGUSR1);
}
