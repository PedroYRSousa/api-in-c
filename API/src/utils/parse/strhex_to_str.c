#include "utils.h"

static int	get_base10(char ref);
static char	strhex_to_char(const u_int8_t *ref);

void	strhex_to_str(const u_int8_t *src, char *dest)
{
	while ((*src))
	{
		(*dest) = strhex_to_char(src);
		dest++;
		src += 2;
	}
}

static int	get_base10(char ref)
{
	if (ref >= '0' && ref <= '9')
		return (int)(ref - '0');
	else if (ref == 'a' || ref == 'A')
		return (10);
	else if (ref == 'b' || ref == 'B')
		return (11);
	else if (ref == 'c' || ref == 'C')
		return (12);
	else if (ref == 'd' || ref == 'D')
		return (13);
	else if (ref == 'e' || ref == 'E')
		return (14);
	else if (ref == 'f' || ref == 'F')
		return (15);
	return (0);
}

static char	strhex_to_char(const u_int8_t *ref)
{
	char	out;

	out = 0;
	out += (get_base10(ref[0]) * 16);
	out += (get_base10(ref[1]));
	return (out);
}
