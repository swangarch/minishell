#include "../../includes/minishell.h"

int 	syntax_error(char c)
{
    printf("%s%s `%c'\n", SHELL, SYN_ERR, c);
	return (TRUE);
}

int 	syntax_error_newline(void)
{
    printf("%s%s\n", SHELL, SYN_ERR_NEWLINE);
	return (TRUE);
}
