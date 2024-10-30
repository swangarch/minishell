/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:00:33 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/22 16:00:34 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	red_in_fromfile(t_cmd *cmd, int *fd_infile, int *i)
{
	int	index_fd;

	index_fd = *i / 2;
	(*i)++;
	fd_infile[index_fd] = open(cmd->redin[*i], O_RDONLY, 0666);
	if (fd_infile[index_fd] < 0)
	{
		ft_putstr_fd(SHELL, 2);
		perror(cmd->redin[*i]);
		close_fds(fd_infile, *i);
		free(fd_infile);
		return (0);
	}
	dup2(fd_infile[index_fd], STDIN_FILENO);
	close(fd_infile[index_fd]);
	return (1);
}

static	int	open_heredoc_read(int *fd_infile, int *i, char *here_doc)
{
	int	index_fd;

	index_fd = *i / 2;
	fd_infile[index_fd] = open(here_doc, O_RDONLY, 0666);
	if (fd_infile[index_fd] < 0)
	{
		ft_putstr_fd(SHELL, 2);
		perror(here_doc);
		close_fds(fd_infile, *i);
		free(fd_infile);
		return (0);
	}
	return (1);
}

static	int	red_in_heredoc(int *fd_infile, int *i, t_shell *shell, int index_p)
{
	int	index_fd;

	index_fd = (*i) / 2;
	(*i)++;
	if (!open_heredoc_read(fd_infile, i, (shell->here_docs)[index_p]))
		return (0);
	dup2(fd_infile[index_fd], STDIN_FILENO);
	close(fd_infile[index_fd]);
	return (1);
}

int	red_in(t_cmd *cmd, t_shell *shell, int index_p)
{
	int	i;
	int	*fd_infile;

	i = -1;
	if (!cmd->redin[0])
		return (1);
	fd_infile = malloc(get_tab_num(cmd->redin) * sizeof(int));
	if (!fd_infile)
		return (0);
	while (cmd->redin[++i])
	{
		if (is_red(cmd->redin[i]) == REDIN)
		{
			if (!red_in_fromfile(cmd, fd_infile, &i))
				return (0);
		}
		else if (is_red(cmd->redin[i]) == 2 && \
			i / 2 == get_tab_num(cmd->redin) / 2 - 1)
		{
			if (!red_in_heredoc(fd_infile, &i, shell, index_p))
				return (0);
		}
	}
	free(fd_infile);
	return (1);
}
