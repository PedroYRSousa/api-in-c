#include "config.h"
#include <stdio.h>

void	show_malformated_msg(void)
{
	fprintf(stderr, "Error: mal formated input: pleas use [exec] [options].\n\
Options: \n\
	-l: \t To simple list.\n\
	-c: \t To colored.\n\
	-a: \t To order asc (ref uri).\n\
	-d: \t To order desc (ref uri).\n\
	-G: \t To show only GET.\n\
	-P: \t To show only POST.\n\
	-U: \t To show only PUT.\n\
	-D: \t To show only DELETE.\n\
	-O: \t To show only OTHERS.\n");
}
