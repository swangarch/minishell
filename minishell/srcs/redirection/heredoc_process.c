/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:13:08 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/29 18:13:09 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	write_heredoc(t_cmd *cmd, int *fd_infile, \
	int *i, t_shell *shell)
{
	char	*line;
	int		index_fd;

	index_fd = *i / 2;
	while (1)
	{
		if (g_sigint_flag)
			return ;
		line = readline("> ");
		if (g_sigint_flag)
			return (free(line), (void)0);
		if (!line)
			return (ft_put3str_fd(MES_DELIM_ERR, cmd->redin[*i], "')\n", \
				STDERR_FILENO), (void)0);
		if (!ft_strcmp(line, cmd->redin[*i]))
			return (free(line), (void)0);
		line = expand_var_here(line, shell->env_head, shell->status);
		write(fd_infile[index_fd], line, ft_strlen(line));
		write(fd_infile[index_fd], "\n", 1);
		free(line);
	}
}

static	int	open_heredoc_create(int *fd_infile, int *i, char *here_doc)
{
	int	index_fd;

	index_fd = *i / 2;
	fd_infile[index_fd] = open(here_doc, O_WRONLY | O_CREAT, 0666);
	if (fd_infile[index_fd] < 0)
	{
		perror(here_doc);
		close_fds(fd_infile, *i);
		return (0);
	}
	return (1);
}

static	char	*create_heredoc(t_shell *shell, int *fd_infile, \
	int *i, int index_p)
{
	char	*here_doc;
	int		index_fd;

	index_fd = *i / 2;
	here_doc = here_doc_name(index_p);
	if (!here_doc)
		return (NULL);
	(*i)++;
	if (!open_heredoc_create(fd_infile, i, here_doc))
		return (NULL);
	write_heredoc(shell->tab_cmd[index_p], fd_infile, i, shell);
	close(fd_infile[index_fd]);
	if (g_sigint_flag)
		return (unlink(here_doc), free(here_doc), NULL);
	if (index_fd != get_tab_num(shell->tab_cmd[index_p]->redin) / 2 - 1)
		return (unlink(here_doc), free(here_doc), here_doc = NULL, \
			ft_strdup(""));
	return (here_doc);
}

int	on_has_heredoc(t_cmd **tab_cmd, t_shell *shell, \
	char **here_docs, int index_p)
{
	int	i;
	int	*fd_infile;

	fd_infile = malloc(get_tab_num(tab_cmd[index_p]->redin) * sizeof(int));
	if (!fd_infile)
		return (free_char_array(here_docs), 0);
	i = 0;
	while (tab_cmd[index_p]->redin[i])
	{
		if (is_red(tab_cmd[index_p]->redin[i]) == HEREDOC)
		{
			here_docs[index_p] = create_heredoc(shell, fd_infile, &i, index_p);
			if (!here_docs[index_p])
				return (free_char_array(here_docs), free(fd_infile), 0);
			else if (!ft_strcmp("", here_docs[index_p]) && i / 2 \
				!= get_tab_num(tab_cmd[index_p]->redin) / 2 - 1)
			{
				free(here_docs[index_p]);
				here_docs[index_p] = NULL;
			}
		}
		i++;
	}
	free(fd_infile);
	return (1);
}

char	**process_heredocs(t_cmd **tab_cmd, t_shell *shell, int num_cmd)
{
	int		index_p;
	char	**here_docs;

	index_p = 0;
	if (!tab_cmd || !shell)
		return (NULL);
	here_docs = malloc(sizeof(char *) * (num_cmd + 1));
	if (!here_docs)
		return (NULL);
	while (index_p < num_cmd)
	{
		if (!has_heredoc(tab_cmd[index_p], shell))
		{
			here_docs[index_p] = ft_strdup("");
			if (!here_docs[index_p++])
				return (free_char_array(here_docs), NULL);
			continue ;
		}
		if (!on_has_heredoc(tab_cmd, shell, here_docs, index_p))
			return (NULL);
		index_p++;
	}
	here_docs[index_p] = NULL;
	return (here_docs);
}
