#include "../../includes/minishell.h"

void	set_prompt(t_shell *shell)
{
    char    *tmp;

    tmp = ft_strjoin(RED, "Minishell>$");
    shell->terminal_prompt = ft_strjoin(tmp, COLOR_E);
    free(tmp);
}
