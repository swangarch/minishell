/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:13:04 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/21 18:13:07 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void close_fds(int *fd, int num)
{
    int i;

    i = 0;
    while(i < num)
    {
        close(fd[i]);
        i++;
    }
}   

char *here_doc_name(int index_p)
{
    int fd_heredoc;
    char *filename;
    char *basename;
    int count;
    char *strnum;

    basename = ".temp_here_doc_++-+-+-+--+";
    count = 0;
    strnum = ft_itoa(count);
    if (!strnum)
        return (NULL);
    
    filename = ft_strjoin(basename, strnum);//free
    filename = ft_strjoin(filename, ft_itoa(index_p));//protect and free
    free(strnum);
    if (!filename)
        return (NULL);

    while (access(filename, F_OK) == 0)
    {
        count++;
        free(filename);
        strnum = ft_itoa(count);
        if (!strnum)
            return (NULL);
        filename = ft_strjoin(basename, strnum);
        free(strnum);
        if (!filename)
            return (NULL);
    }
    return (filename);
}

int has_heredoc(t_cmd *cmd, t_shell *shell)
{
    int i;

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

void    write_heredoc(t_cmd *cmd, int *fd_infile, int *i, t_shell *shell)
{
    char *line;
    int index_fd = *i / 2;
    //char    *prompt = ft_strdup("> ");//for test!!!!!11

    line = readline("> ");///free
    add_history(line);
    line = expand_var_here(line, shell->env_head, shell->status);
    while (ft_strcmp(line, cmd->redin[*i]))
    {
        write(fd_infile[index_fd], line, ft_strlen(line));
        write(fd_infile[index_fd], "\n", 1);
        free(line);
        line = readline("> ");
        add_history(line);
        line = expand_var_here(line, shell->env_head, shell->status);
    }
    free(line);
    //free(prompt);
}

int red_open_heredoc(int *fd_infile, int *i, char *here_doc)
{
    int index_fd;

    index_fd = *i / 2;
    fd_infile[index_fd] = open(here_doc, O_RDWR | O_CREAT, 0666);
    if (fd_infile[index_fd] < 0)
    {
        perror(here_doc);
        close_fds(fd_infile, *i);
        free(fd_infile);
        return (0);
    }
    return (1);
}

int red_in_heredoc(t_cmd *cmd, int *fd_infile, int *i, t_shell *shell, int index_p)
{
    char *here_doc;
    int index_fd;

    index_fd = *i / 2;
    here_doc = here_doc_name(index_p);
    if (!here_doc)
        return (0);

    (*i)++;
    if (!red_open_heredoc(fd_infile, i, here_doc))
        return (0);
    write_heredoc(cmd, fd_infile, i, shell);
    close(fd_infile[index_fd]);
    if (!(index_fd == get_tab_num(cmd->redin) / 2 - 1))
    {
        unlink(here_doc);
        return (1);
    }
    if (!red_open_heredoc(fd_infile, i, here_doc))
        return (0);
    dup2(fd_infile[index_fd], STDIN_FILENO);
    close(fd_infile[index_fd]);
    return (1);
}

void red_in(t_cmd *cmd, t_shell *shell, int index_p)
{
    int i = 0;
    int index_fd = 0;
    int *fd_infile;

    if (!cmd->redin[i])
        return;
    fd_infile = malloc(get_tab_num(cmd->redin) * sizeof(int));
    if (!fd_infile)
    {
        ft_err(MES_MALLOC_ERR);
        return ;
    }
    while (cmd->redin[i])
    {
        if (is_red(cmd->redin[i]) == REDIN)
        {
            if (!red_in_fromfile(cmd, fd_infile, &i))
                return ;
        }
        else if (is_red(cmd->redin[i]) == HEREDOC)
        {
            if (!red_in_heredoc(cmd, fd_infile, &i, shell, index_p))
                return ;
        }
        i++;
        index_fd++;
    }
    free(fd_infile);
}


int red_out_tofile(t_cmd *cmd, int *fd_outfile, int *i)
{
    int index_fd;

    index_fd = (*i) / 2;
    (*i)++;
    fd_outfile[index_fd] = open(cmd->redout[*i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd_outfile[index_fd] < 0)
    {
        perror(cmd->redout[*i]);
        close_fds(fd_outfile, *i);
        free(fd_outfile);
        //freeshell cmd
        return (0);
    }
    return (1);
}

int red_out_append(t_cmd *cmd, int *fd_outfile, int *i)
{
    int index_fd;

    index_fd = (*i) / 2;
    (*i)++;
    fd_outfile[index_fd] = open(cmd->redout[*i], O_CREAT | O_WRONLY | O_APPEND, 0666);
    if (fd_outfile[index_fd] < 0)
    {
        perror(cmd->redout[*i]);
        close_fds(fd_outfile, *i);
        free(fd_outfile);
        //freeshell cmd
        return (0);
    }
    return (1);
}

void red_out(t_cmd *cmd, t_shell *shell)
{
    int i = 0;
    int index_fd = 0;
    int *fd_outfile;

    if (!cmd->redout[i])
        return;
    fd_outfile = malloc(get_tab_num(cmd->redout) * sizeof(int));
    if (!fd_outfile)
    {
        ft_err(MES_MALLOC_ERR);
        return ;
    }
    while (cmd->redout[i])
    {
        if (is_red(cmd->redout[i]) == REDOUT)
        {
            if (!red_out_tofile(cmd, fd_outfile, &i))
                return ;
        }
        else if (is_red(cmd->redout[i]) == APPEND)
        {
            if (!red_out_append(cmd, fd_outfile, &i))
                return ;
        }
        i++;
        index_fd++;
    }
    dup2(fd_outfile[index_fd - 1], STDOUT_FILENO);
    close(fd_outfile[index_fd - 1]);
    free(fd_outfile);    
}
