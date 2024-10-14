#include "../../includes/minishell.h"

int 	syntax_error(char c)
{
    ft_putstr_fd(SHELL SYN_ERR " `", STDERR_FILENO);
    write(STDERR_FILENO, &c, 1);
    ft_putstr_fd("'\n", STDERR_FILENO);
	return (TRUE);
}

int 	syntax_error_newline(void)
{
    ft_putstr_fd(SHELL SYN_ERR_NEWLINE "\n", STDERR_FILENO);
	return (TRUE);
}
