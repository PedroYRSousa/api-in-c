#ifndef DISPLAY_H
# define DISPLAY_H

#ifndef FILTER_GET
# define FILTER_GET 01
#endif
#ifndef FILTER_POST
# define FILTER_POST 02
#endif
#ifndef FILTER_PUT
# define FILTER_PUT 03
#endif
#ifndef FILTER_DELETE
# define FILTER_DELETE 04
#endif
#ifndef FILTER__OTHERS
# define FILTER__OTHERS 05
#endif

#ifndef COLOR_GET
# define COLOR_GET 33
#endif
#ifndef COLOR_POST
# define COLOR_POST 34
#endif
#ifndef COLOR_PUT
# define COLOR_PUT 35
#endif
#ifndef COLOR_DELETE
# define COLOR_DELETE 36
#endif
#ifndef COLOR_OTHERS
# define COLOR_OTHERS 90
#endif

# include "config.h"
# include "request.h"
# include "display/list.h"
# include "display/table.h"

void	set_color(t_config config, t_list *list);
void	display_list(t_config config, t_list *list);
void	display_table(t_config config, t_table *table);
void	display_log(t_config config, t_request *requests);

#endif