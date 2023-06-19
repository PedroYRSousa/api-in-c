#include "config.h"
#include <stdio.h>
#include <string.h>

static t_config	init_config()
{
	t_config	config;

	config.filter = 0;
	config.is_valid = 0;
	config.is_colored = 0;
	config.is_ordened = 0;
	config.method_display = 0;
	return (config);
}

static int	get_argument(char *arg)
{
	int	info = 00;

	if (strlen(arg) == 1)
		return (MALF_FORMATED);
	if ((*arg) != '-')
		return (MALF_FORMATED);
	arg++;
	while ((*arg))
	{
		if ((*arg) == 'l')
			info |= (LIST);
		else if ((*arg) == 'c')
			info |= (COLORED);
		else if ((*arg) == 'a')
			info |= (ORDENED_ASC);
		else if ((*arg) == 'd')
			info |= (ORDENED_DEC);
		else if ((*arg) == 'G')
			info |= (ONLY_GET);
		else if ((*arg) == 'P')
			info |= (ONLY_POST);
		else if ((*arg) == 'U')
			info |= (ONLY_PUT);
		else if ((*arg) == 'D')
			info |= (ONLY_DELETE);
		else if ((*arg) == 'O')
			info |= (ONLY_OTHERS);
		else
			info |= (MALF_FORMATED);
		arg++;
	}
	return (info);
}

static t_config	get_config(int info)
{
	t_config	config = init_config();

	config.is_valid = !(info % 8);
	info /= 8;
	config.is_colored = (info % 8);
	info /= 8;
	config.is_ordened = (info % 8);
	info /= 8;
	config.filter = (info % 8);
	info /= 8;
	config.filter_get = (info % 8);
	info /= 8;
	config.filter_post = (info % 8);
	info /= 8;
	config.filter_put = (info % 8);
	info /= 8;
	config.filter_delete = (info % 8);
	info /= 8;
	config.filter_others = (info % 8);
	info /= 8;
	config.method_display = (info % 8);
	return (config);
}

t_config	load_config(char **argv)
{
	int	info = (TABLE | NOT_ORDENED | SHOW_ALL);

	argv++;
	while ((*argv) && !(info % 8))
	{
		info = (info | get_argument((*argv)));
		argv++;
	}
	return (get_config(info));
}