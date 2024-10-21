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

void red_in(t_strcmd *str_cmd, t_shell *shell)
{
    char **redin;
    redin = str_cmd->redin;
    int i = 0;
    int index_fd = 0;
    int *fd_infile;
    char *line;

    if (!redin[i])
    {
        return;
    }
    fd_infile = malloc(str_cmd->num_redin * sizeof(int));
    if (!fd_infile)
    {
        ft_err(MES_MALLOC_ERR);
        return ;
    }
    while (redin[i])
    {
        if (is_red(redin[i]) == REDIN)
        {
            i++;
            fd_infile[index_fd] = open(redin[i], O_RDONLY);
            if (fd_infile[index_fd] < 0)
            {
                perror("open infile");
                close_fds(fd_infile, i);
                free(fd_infile);
                return ;
            }
            dup2(fd_infile[index_fd], STDIN_FILENO);
            close(fd_infile[index_fd]);
        }
        else if (is_red(redin[i]) == HEREDOC)
        {
            i++;
            fd_infile[index_fd] = open("here_doc", O_RDWR | O_CREAT, 0666);
            if (fd_infile[index_fd] < 0)
            {
                perror("here_doc");
                close_fds(fd_infile, i);
                free(fd_infile);
                return ;
            }
            line = get_next_line(STDIN_FILENO);
            while (!(ft_strncmp(line, redin[i], ft_strlen(redin[i])) == 0 && line[ft_strlen(redin[i])] == '\n'))
            {
                write(fd_infile[index_fd], line, ft_strlen(line));
                free(line);
                line = get_next_line(STDIN_FILENO);
            }
            free(line);
            close(fd_infile[index_fd]);
            fd_infile[index_fd] = open("here_doc", O_RDONLY, 0666);
            dup2(fd_infile[index_fd], STDIN_FILENO);
            close(fd_infile[index_fd]);
        }
        i++;
        index_fd++;
    }
    free(fd_infile);
}

void red_out(t_strcmd *str_cmd, t_shell *shell)
{
    char **redout;
    redout = str_cmd->redout;
    int i = 0;
    int index_fd = 0;
    int *fd_outfile;

    if (!redout[i])
    {
        return;
    }
    fd_outfile = malloc(str_cmd->num_redout * sizeof(int));

    if (!fd_outfile)
    {
        ft_err(MES_MALLOC_ERR);
        return ;
    }
    while (redout[i])
    {
        if (is_red(redout[i]) == REDOUT)
        {
            i++;
            fd_outfile[index_fd] = open(redout[i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
            if (fd_outfile[index_fd] < 0)
            {
                perror(redout[i]);
                close_fds(fd_outfile, i);
                free(fd_outfile);
                return ;
            }
        }
        else if (is_red(redout[i]) == APPEND)
        {
            i++;
            fd_outfile[index_fd] = open(redout[i], O_CREAT | O_WRONLY | O_APPEND, 0666);///Here can be optimized???i++
            if (fd_outfile[index_fd] < 0)
            {
                perror(redout[i]);
                close_fds(fd_outfile, i);
                free(fd_outfile);
                return ;
            }
        }
        //dup2(fd_outfile[i / 2], STDOUT_FILENO);
        //close(fd_outfile[i / 2]);
        i++;
        index_fd++;
    }
    dup2(fd_outfile[index_fd - 1], STDOUT_FILENO);
    close(fd_outfile[index_fd - 1]);
    free(fd_outfile);    
}

void    exec_cmd(t_strcmd *str_cmd, t_shell *shell)
{
    red_in(str_cmd, shell);
    red_out(str_cmd, shell);
}