#include "io.h"

void	load_requests(char *file, t_request **root)
{
	while (file)
		add_request(get_request(&file), root);
}
