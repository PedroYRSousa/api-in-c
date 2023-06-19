#include <regex.h>
#include "utils.h"

bool	exec_regex(const char *expression, char *target)
{
	regex_t	regex;

	if (regcomp(&regex, expression, REG_EXTENDED))
	{
		fprintf(stderr, "Erro ao gerar o regex");
		return (false);
	}

	if (!regexec(&regex, target, 0, NULL, 0))
	{
		regfree(&regex);
		return (true);
	}
	else
	{
		regfree(&regex);
		return (false);
	}
}

bool	is_valid_username(char *username)
{
	const char	*expression = "^([A-Za-z0-9]){4,20}$";

	return (exec_regex(expression, username));
}

bool	is_valid_email(char *email)
{
	const char	*expression = "[a-zA-Z0-9]+@[a-zA-Z0-9]+\\.[a-z]{2,4}$";

	return (exec_regex(expression, email));
}