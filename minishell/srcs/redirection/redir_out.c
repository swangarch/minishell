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

int	red_out_tofile(t_cmd *cmd, int *fd_outfile, int *i)
{
	int		index_fd;
	char	*info;

	index_fd = (*i) / 2;
	(*i)++;
	fd_outfile[index_fd] = open(cmd->redout[*i], O_CREAT \
		| O_WRONLY | O_TRUNC, 0666);
	if (fd_outfile[index_fd] < 0)
	{
		info = ft_strjoin(SHELL, cmd->redout[*i]);
		perror(info);
		close_fds(fd_outfile, *i / 2);
		free(fd_outfile);
		free(info);
		return (0);
	}
	return (1);
}

int	red_out_append(t_cmd *cmd, int *fd_outfile, int *i)
{
	int		index_fd;
	char	*info;

	index_fd = (*i) / 2;
	(*i)++;
	fd_outfile[index_fd] = open(cmd->redout[*i], O_CREAT \
		| O_WRONLY | O_APPEND, 0666);
	if (fd_outfile[index_fd] < 0)
	{
		info = ft_strjoin(SHELL, cmd->redout[*i]);
		perror(info);
		close_fds(fd_outfile, *i / 2);
		free(fd_outfile);
		free(info);
		return (0);
	}
	return (1);
}

void	dup_last(int *fd_outfile, int i)
{
	dup2(fd_outfile[i / 2 - 1], STDOUT_FILENO);
	close(fd_outfile[i / 2 - 1]);
}

int	red_out(t_cmd *cmd)
{
	int	i;
	int	*fd_outfile;

	i = -1;
	if (!cmd->redout[0])
		return (1);
	fd_outfile = malloc((get_tab_num(cmd->redout) / 2) * sizeof(int));
	if (!fd_outfile)
		return (0);
	while (cmd->redout[++i])
	{
		if (is_red(cmd->redout[i]) == REDOUT)
		{
			if (!red_out_tofile(cmd, fd_outfile, &i))
				return (0);
		}
		else if (is_red(cmd->redout[i]) == APPEND)
		{
			if (!red_out_append(cmd, fd_outfile, &i))
				return (0);
		}
	}
	dup_last(fd_outfile, i);
	free(fd_outfile);
	return (1);
}
