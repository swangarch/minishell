/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:13:21 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/29 18:13:27 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	*join_here_doc_name(int count, int index_p)
{
	char	*basename;
	char	*strnum;
	char	*heredocnum;
	char	*here_doc_name;

	basename = "/tmp/.heredoc++-+-+-+--+";
	strnum = ft_itoa(count);
	if (!strnum)
		return (NULL);
	heredocnum = ft_itoa(index_p);
	if (!heredocnum)
	{
		free(strnum);
		return (NULL);
	}
	here_doc_name = ft_str4join(basename, strnum, "_", heredocnum);
	free(strnum);
	free(heredocnum);
	return (here_doc_name);
}

char	*here_doc_name(int index_p)
{
	char	*filename;
	int		count;

	count = 0;
	filename = join_here_doc_name(count, index_p);
	if (!filename)
		return (NULL);
	while (access(filename, F_OK) == 0)
	{
		count++;
		free(filename);
		filename = join_here_doc_name(count, index_p);
		if (!filename)
			return (NULL);
	}
	return (filename);
}

int	has_heredoc(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	if (!cmd || !shell)
		return (0);
	while (cmd->redin[i])
	{
		if (is_red(cmd->redin[i]) == HEREDOC)
			return (1);
		i++;
	}
	return (0);
}

void	delete_heredoc(char **here_docs)
{
	int	i;

	if (!here_docs)
		return ;
	i = 0;
	while (here_docs[i])
	{
		if (ft_strcmp("", here_docs[i]) && access(here_docs[i], F_OK) == 0)
			unlink(here_docs[i]);
		free(here_docs[i]);
		here_docs[i] = NULL;
		i++;
	}
	free(here_docs);
	here_docs = NULL;
}
