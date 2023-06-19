#include "utils.h"

void	str_to_strhex(const u_int8_t *src, char *dest)
{
	while ((*src))
	{
		sprintf(dest, "%02x", (*src));
		dest += 2;
		src++;
	}
}
