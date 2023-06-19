#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void show_default_row(t_string row, int index)
{
	char	*aux;

	aux = strndup(row.ptr, row.size);
	if (index != 3)
		printf("|%*s%*s", (int)((SIZE_TABLE / 2) + (strlen(aux) / 2)), aux, (int)((SIZE_TABLE / 2) - (strlen(aux) / 2)), "");
	else
		printf("|    %-*s%*s", (int)((SIZE_TABLE / 2) + (strlen(aux) / 2)), aux, (int)((SIZE_TABLE / 2) - (strlen(aux) / 2) - 4), "");
	free(aux);
}

static void show_default_colunm(size_t coll_1, t_string coll_2, t_string coll_3)
{
	char		aux[20];
	t_string	aux_aux;

	sprintf(aux, "%zu", coll_1);
	aux_aux.ptr = aux;
	aux_aux.size = strlen(aux);
	show_default_row(aux_aux, 1);
	show_default_row(coll_2, 2);
	show_default_row(coll_3, 3);
	printf("|\n");
}

static void	show_header(void)
{
	printf("\e[107m\e[30m");
	printf("|%*s%*s", (int)((SIZE_TABLE / 2) + (strlen("Total Requests") / 2)), "Total Requests", (int)((SIZE_TABLE / 2) - (strlen("Total Requests") / 2)), "");
	printf("|%*s%*s", (int)((SIZE_TABLE / 2) + (strlen("HTTP method") / 2)), "HTTP method", (int)((SIZE_TABLE / 2) - (strlen("HTTP method") / 2)), "");
	printf("|%*s%*s", (int)((SIZE_TABLE / 2) + (strlen("Path") / 2)), "Path", (int)((SIZE_TABLE / 2) - (strlen("Path") / 2)), "");
	printf("|\n");
	printf("\e[0m");
}

static void	show_by_filter(t_config config, t_table *table, char *filter)
{
	while (table)
	{
		set_color(config, table->row);
		if (strncmp(table->row->raw.method.ptr, filter, table->row->raw.method.size) == 0)
			show_default_colunm(table->count, table->row->raw.method, table->row->raw.uri);
		table = table->next;
		printf("\e[0m");
	}
}

void	display_table(t_config config, t_table *table)
{
	show_header();

	if (config.filter)
	{
		if (config.filter_get)
			show_by_filter(config, table, "GET");
		if (config.filter_post)
			show_by_filter(config, table, "POST");
		if (config.filter_put)
			show_by_filter(config, table, "PUT");
		if (config.filter_delete)
			show_by_filter(config, table, "DELETE");
		if (config.filter_others)
			show_by_filter(config, table, "OTHERS");
	}
	else
	{
		show_by_filter(config, table, "GET");
		show_by_filter(config, table, "POST");
		show_by_filter(config, table, "PUT");
		show_by_filter(config, table, "DELETE");
		show_by_filter(config, table, "OTHERS");
	}
}
