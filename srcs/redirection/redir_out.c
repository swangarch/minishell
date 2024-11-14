/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:00:41 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/22 16:00:43 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(int *fd, int num)
{
	int	i;

	i = 0;
	if (!fd)
		return ;
	while (i < num)
	{
		if (fd[i] >= 0)
			close(fd[i]);
		i++;
	}
}

int	last_redout(t_cmd *cmd, int i)
{
	i++;
	while (cmd->red[i])
	{
		if (is_red(cmd->red[i]) == REDOUT || is_red(cmd->red[i]) == APPEND)
			return (0);
		i++;
	}
	return (1);
}

int	last_redin(t_cmd *cmd, int i)
{
	i++;
	while (cmd->red[i])
	{
		if (is_red(cmd->red[i]) == REDIN || is_red(cmd->red[i]) == HEREDOC)
			return (0);
		i++;
	}
	return (1);
}

int	red_out_tofile(t_cmd *cmd, int *fd_outfile, int *i)
{
	int		index_fd;
	char	*info;

	index_fd = (*i) / 2;
	(*i)++;
	fd_outfile[index_fd] = open(cmd->red[*i], O_CREAT \
		| O_WRONLY | O_TRUNC, 0666);
	if (fd_outfile[index_fd] < 0)
	{
		info = ft_strjoin(SHELL, cmd->red[*i]);
		perror(info);
		close_fds(fd_outfile, *i / 2);
		free(fd_outfile);
		free(info);
		return (0);
	}
	if (last_redout(cmd, *i))
		dup2(fd_outfile[index_fd], STDOUT_FILENO);
	close(fd_outfile[index_fd]);
	return (1);
}

int	red_out_append(t_cmd *cmd, int *fd_outfile, int *i)
{
	int		index_fd;
	char	*info;

	index_fd = (*i) / 2;
	(*i)++;
	fd_outfile[index_fd] = open(cmd->red[*i], O_CREAT \
		| O_WRONLY | O_APPEND, 0666);
	if (fd_outfile[index_fd] < 0)
	{
		info = ft_strjoin(SHELL, cmd->red[*i]);
		perror(info);
		close_fds(fd_outfile, *i / 2);
		free(fd_outfile);
		free(info);
		return (0);
	}
	if (last_redout(cmd, *i))
		dup2(fd_outfile[index_fd], STDOUT_FILENO);
	close(fd_outfile[index_fd]);
	return (1);
}
