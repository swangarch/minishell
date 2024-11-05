/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:07:29 by yfan              #+#    #+#             */
/*   Updated: 2024/10/29 18:07:31 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_before_exit(t_shell *shell)
{
	rl_clear_history();
	set_close(shell->std_fds);
	free_in_loop(shell);
	delete_heredoc(shell->here_docs);
	free_char_array(shell->env);
	free_env(shell->env_head);
	free(shell->home_path);
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
		free_char_array(shell->tab_cmd[i]->red);
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

void	free_save_line(t_shell *shell, int *p_fd, char *path)
{
	free_before_exit(shell);
	free(p_fd);
	free(path);
}
