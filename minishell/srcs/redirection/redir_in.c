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
	int		index_fd;
	char	*info;

	index_fd = *i / 2;
	(*i)++;
	fd_infile[index_fd] = open(cmd->red[*i], O_RDONLY, 0666);
	if (fd_infile[index_fd] < 0)
	{
		info = ft_strjoin(SHELL, cmd->red[*i]);
		perror(info);
		close_fds(fd_infile, *i / 2);
		free(fd_infile);
		free(info);
		return (0);
	}
	if (last_redin(cmd, *i))
		dup2(fd_infile[index_fd], STDIN_FILENO);
	close(fd_infile[index_fd]);
	return (1);
}

static	int	open_heredoc_read(int *fd_infile, int *i, char *here_doc)
{
	int		index_fd;
	char	*info;

	index_fd = *i / 2;
	fd_infile[index_fd] = open(here_doc, O_RDONLY, 0666);
	if (fd_infile[index_fd] < 0)
	{
		info = ft_strjoin(SHELL, here_doc);
		perror(info);
		close_fds(fd_infile, *i / 2);
		free(fd_infile);
		free(info);
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
	if (last_redin(shell->tab_cmd[index_p], *i))
		dup2(fd_infile[index_fd], STDIN_FILENO);
	close(fd_infile[index_fd]);
	return (1);
}

int	check_flag(int	*fd_redfile, t_shell *shell, int index_p, int *i)
{
	t_cmd	*cmd;

	cmd = shell->tab_cmd[index_p];
	if (is_red(cmd->red[*i]) == REDIN)
	{
		if (!red_in_fromfile(cmd, fd_redfile, i))
			return (0);
	}
	else if (is_red(cmd->red[*i]) == HEREDOC && last_redin(cmd, *i))
	{
		if (!red_in_heredoc(fd_redfile, i, shell, index_p))
			return (0);
	}
	else if (is_red(cmd->red[*i]) == REDOUT)
	{
		if (!red_out_tofile(cmd, fd_redfile, i))
			return (0);
	}
	else if (is_red(cmd->red[*i]) == APPEND)
	{
		if (!red_out_append(cmd, fd_redfile, i))
			return (0);
	}
	return (1);
}

int	redir(t_cmd *cmd, t_shell *shell, int index_p)
{
	int	i;
	int	*fd_redfile;

	i = -1;
	if (!cmd->red[0])
		return (1);
	fd_redfile = malloc((get_tab_num(cmd->red) / 2) * sizeof(int));
	if (!fd_redfile)
		return (0);
	while (cmd->red[++i])
	{
		if (!check_flag(fd_redfile, shell, index_p, &i))
			return (0);
	}
	return (free(fd_redfile), 1);
}
