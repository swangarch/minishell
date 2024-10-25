#include "../../includes/minishell.h"

// void	ft_add_history(t_shell *shell)
// {
//     int flag;

//     flag = FALSE;
//     if (shell->prompt[0] && !is_only_space(shell->prompt)
// 		&& !rep_prompt(shell->prompt, shell->prev_prompt))
// 	{
// 		if (shell->prev_prompt)
// 			free(shell->prev_prompt);
// 		add_history(shell->prompt);
// 		flag = TRUE;
// 	}
// 	if (flag)
// 		shell->prev_prompt = shell->prompt;
// 	else
// 		free(shell->prompt);
// 	free(shell->trimmed_prompt);
// 	if (shell->exit_code == 0)
// 		shell->cmd_has_been_executed = TRUE;
// 	else
// 		shell->cmd_has_been_executed = FALSE;
// }

// int	    is_only_space(char *str)
// {
// 	int	i;

// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (!(str[i] == ' ' || (str[i] > 7) && str[i] < 14))
// 			return (FALSE);
// 	}
// 	return (TRUE);
// }

// int 	rep_prompt(char *prompt, char *prev_prompt)
// {
// 	if (prev_prompt == NULL || ft_strcmp(prompt, prev_prompt))
// 		return (FALSE);
// 	return (TRUE);
// }
