#ifndef USER_MODEL_H
# define  USER_MODEL_H

#include "utils.h"

char	*valid_user(bson_t	*user);
char	*valid_user_update(bson_t	*user);
void	get_value_user(bson_t doc, bson_t *user);

#endif