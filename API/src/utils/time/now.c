#include "utils.h"

time_t	now(void)
{
	struct timeval	tv;
	time_t			now;

	gettimeofday(&tv, NULL);
	now = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));

	return (now);
}
