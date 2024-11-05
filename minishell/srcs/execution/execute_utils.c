/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:53:53 by yfan              #+#    #+#             */
/*   Updated: 2024/10/28 18:53:55 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_pipe_fds(int **p_fd, int num_cmd, t_shell *shell)
{
	int	i;

	if (!p_fd)
		return (1);
	*p_fd = malloc(2 * (num_cmd - 1) * sizeof(int));
	if (!*p_fd)
	{
		shell->status = 1;
		return (1);
	}
	i = 0;
	while (i < num_cmd - 1)
	{
		if (pipe(*p_fd + i * 2) == -1)
		{
			shell->status = 2;
			perror(SHELL "pipe");
			free(*p_fd);
			return (1);
		}
		++i;
	}
	return (0);
}

void	close_multi_fd(int num, int *p_fd)
{
	int	i;

	i = 0;
	while (i < 2 * (num - 1))
		close(p_fd[i++]);
}

void	set_child(int *num, int *p_fd, t_shell *shell, t_cmd *cmd)
{
	if (num[1] > 0)
	{
		if (dup2(p_fd[(num[1] - 1) * 2], 0) == -1)
		{
			perror(SHELL "dup2");
			free_close(shell, p_fd, num[0]);
			exit(EXIT_FAILURE);
		}
	}
	if (num[1] < num[0] - 1)
	{
		if (dup2(p_fd[num[1] * 2 + 1], 1) == -1)
		{
			perror(SHELL "dup2");
			free_close(shell, p_fd, num[0]);
			exit(EXIT_FAILURE);
		}
	}
	if (!redir(cmd, shell, num[1]))
	{
		free_close(shell, p_fd, num[0]);
		exit(EXIT_FAILURE);
	}
	close_multi_fd(num[0], p_fd);
}

void	final_execute(t_shell *shell, char *path, char **cmd, int *p_fd)
{
	if (execve(path, cmd, shell->env) == -1)
	{
		free_save_line(shell, p_fd, path);
		perror("execve");
		exit(126);
	}
}
