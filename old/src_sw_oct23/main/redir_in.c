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

#include "../includes/minishell.h"

int red_in_fromfile(t_cmd *cmd, int *fd_infile, int *i)
{
    int index_fd = *i / 2;

    (*i)++;
    fd_infile[index_fd] = open(cmd->redin[*i], O_RDONLY);
    if (fd_infile[index_fd] < 0)
    {
        perror("open infile");
        close_fds(fd_infile, *i);
        free(fd_infile);
        return (0);
    }
    dup2(fd_infile[index_fd], STDIN_FILENO);
    close(fd_infile[index_fd]);
    return (1);
}

int open_heredoc_read(int *fd_infile, int *i, char *here_doc)
{
    int index_fd;

    index_fd = *i / 2;
    fd_infile[index_fd] = open(here_doc, O_RDONLY, 0666);
    if (fd_infile[index_fd] < 0)
    {
        perror(here_doc);
        close_fds(fd_infile, *i);
        free(fd_infile);
        return (0);
    }
    return (1);
}

int red_in_heredoc(int *fd_infile, int *i, t_shell *shell, int index_p, char **here_docs)
{
    char *here_doc;
    int index_fd;

    index_fd = (*i) / 2;
    (*i)++;
    if (!open_heredoc_read(fd_infile, i, here_docs[index_p]))
        return (0);
    dup2(fd_infile[index_fd], STDIN_FILENO);
    close(fd_infile[index_fd]);
    return (1);
}

void red_in(t_cmd *cmd, t_shell *shell, int index_p, char **here_docs)
{
    int i = 0;
    int *fd_infile;

    if (!cmd->redin[i])
        return;
    fd_infile = malloc(get_tab_num(cmd->redin) * sizeof(int));
    if (!fd_infile)
    {
        ft_err(MES_MALLOC_ERR "case 4");
        return ;
    }
    while (cmd->redin[i])
    {
        if (is_red(cmd->redin[i]) == REDIN)
        {
            if (!red_in_fromfile(cmd, fd_infile, &i))
                return ;
        }
        else if (is_red(cmd->redin[i]) == HEREDOC && i / 2 == get_tab_num(cmd->redin) / 2 - 1)
        {
            if (!red_in_heredoc(fd_infile, &i, shell, index_p, here_docs))
                return ;
        }
        i++;
    }
    free(fd_infile);
}