#include "display.h"
#include <stdio.h>
#include <string.h>

static void	show_simple_row(t_raw_data row)
{	
	printf("%.*s ", (int)row.user_ip.size, row.user_ip.ptr);
	printf("%.*s ", (int)row.date_time.size, row.date_time.ptr);
	printf("%-11.*s ", (int)row.method.size, row.method.ptr);
	printf("%-31.*s ", (int)row.uri.size, row.uri.ptr);
	printf("%-8.*s ", (int)row.status.size, row.status.ptr);
	printf("%-8.*s ", (int)row.size_res.size, row.size_res.ptr);
	printf("%11.*s ", (int)row.time_response.size, row.time_response.ptr);
	printf("\n\e[0m");
}

static void	show_header(void)
{
	printf("\e[107m\e[30m");
	printf("\e[107m\e[30m %*s%*s", (int)((15/ 2) + (strlen("IP") / 2)), "IP", (int)((15/ 2) - (strlen("IP") / 2)), "");
	printf("\e[0m ");
	printf("\e[107m\e[30m %*s%*s", (int)((19 / 2) + (strlen("Date time") / 2)), "Date time", (int)((19 / 2) - (strlen("Date time") / 2)), "");
	printf("\e[0m ");
	printf("\e[107m\e[30m %*s%*s", (int)((10 / 2) + (strlen("Method") / 2)), "Method", (int)((10 / 2) - (strlen("Method") / 2)), "");
	printf("\e[0m ");
	printf("\e[107m\e[30m %*s%*s", (int)((30 / 2) + (strlen("URI") / 2)), "URI", (int)((30 / 2) - (strlen("URI") / 2)), "");
	printf("\e[0m ");
	printf("\e[107m\e[30m %*s%*s", (int)((4 / 2) + (strlen("Status") / 2)), "Status", (int)((4 / 2) - (strlen("Status") / 2)), "");
	printf("\e[0m ");
	printf("\e[107m\e[30m%*s%*s", (int)((8 / 2) + (strlen("Size") / 2)), "Size", (int)((8 / 2) - (strlen("Size") / 2)), "");
	printf("\e[0m ");
	printf("\e[107m\e[30m %*s%*s", (int)((10 / 2) + (strlen("Time (ms)") / 2)), "Time (ms)", (int)((10 / 2) - (strlen("Time (ms)") / 2)), "");
	printf("\e[0m\n");
}

void	display_list(t_config config, t_list *list)
{
	show_header();
	while (list)
	{
		set_color(config, list);
		if (config.filter)
		{
			if (config.filter_get && (!strncmp(list->raw.method.ptr, "GET", list->raw.method.size)))
				show_simple_row(list->raw);
			if (config.filter_post && (!strncmp(list->raw.method.ptr, "POST", list->raw.method.size)))
				show_simple_row(list->raw);
			if (config.filter_put && (!strncmp(list->raw.method.ptr, "PUT", list->raw.method.size)))
				show_simple_row(list->raw);
			if (config.filter_delete && (!strncmp(list->raw.method.ptr, "DELETE", list->raw.method.size)))
				show_simple_row(list->raw);
			if (config.filter_others && (!strncmp(list->raw.method.ptr, "OTHERS", list->raw.method.size)))
				show_simple_row(list->raw);
		}
		else
			show_simple_row(list->raw);
		list = list->next;
	}
}
