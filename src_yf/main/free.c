#include "../includes/minishell.h"

void    free_before_exit(t_shell *shell)
{
	rl_clear_history();
	close(shell->std_fds[0]);
	close(shell->std_fds[1]);
    free_in_loop(shell);
	delete_heredoc(shell->here_docs);
	free_char_array(shell->env);
	free_env(shell->env_head);
}

void	free_char_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_in_loop(t_shell *shell)
{
	int	i;
	
	i = 0;
	free(shell->prompt);
    free(shell->trimmed_prompt);
    free(shell->terminal_prompt);
	shell->prompt = NULL;
    shell->trimmed_prompt = NULL;
    shell->terminal_prompt = NULL;
	while (shell->tab_cmd && shell->tab_cmd[i])
	{
		free_char_array(shell->tab_cmd[i]->redin);
		free_char_array(shell->tab_cmd[i]->redout);
		free_char_array(shell->tab_cmd[i]->cmd);
		i++;
	}
	i = 0;
	while (shell->tab_cmd && shell->tab_cmd[i])
	{
		free(shell->tab_cmd[i]);
		i++;
	}
	free(shell->tab_cmd);
	shell->tab_cmd = NULL;
}

void	free_2_char(char *s1, char *s2)
{
	free(s1);
	free(s2);
}
