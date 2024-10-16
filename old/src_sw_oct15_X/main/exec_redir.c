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

// void red_in(t_strcmd *str_cmd, t_shell *shell)
// {
//     char **redin;
//     redin = str_cmd->redin;
//     int i = 0;
//     int index_fd = 0;
//     int *fd_infile;
//     char *line;

//     if (!redin[i])
//     {
//         return;
//     }
//     fd_infile = malloc(str_cmd->num_redin * sizeof(int));
//     if (!fd_infile)
//     {
//         ft_err(MES_MALLOC_ERR);
//         return ;
//     }
//     while (redin[i])
//     {
//         if (is_red(redin[i]) == REDIN)
//         {
//             i++;
//             fd_infile[index_fd] = open(redin[i], O_RDONLY);
//             if (fd_infile[index_fd] < 0)
//             {
//                 perror("open infile");
//                 close_fds(fd_infile, i);
//                 free(fd_infile);
//                 return ;
//             }
//             dup2(fd_infile[index_fd], STDIN_FILENO);
//             close(fd_infile[index_fd]);
//         }
//         else if (is_red(redin[i]) == HEREDOC)
//         {
//             i++;
//             fd_infile[index_fd] = open("here_doc", O_RDWR | O_CREAT, 0666);
//             if (fd_infile[index_fd] < 0)
//             {
//                 perror("here_doc");
//                 close_fds(fd_infile, i);
//                 free(fd_infile);
//                 return ;
//             }
//             line = get_next_line(STDIN_FILENO);
//             while (!(ft_strncmp(line, redin[i], ft_strlen(redin[i])) == 0 && line[ft_strlen(redin[i])] == '\n'))
//             {
//                 write(fd_infile[index_fd], line, ft_strlen(line));
//                 free(line);
//                 line = get_next_line(STDIN_FILENO);
//             }
//             free(line);
//             close(fd_infile[index_fd]);
//             fd_infile[index_fd] = open("here_doc", O_RDONLY, 0666);
//             dup2(fd_infile[index_fd], STDIN_FILENO);
//             close(fd_infile[index_fd]);
//         }
//         i++;
//         index_fd++;
//     }
//     free(fd_infile);
// }

char *here_doc_name(void)
{
    int fd_heredoc;
    char *filename;
    char *basename;
    int count;
    char *strnum;

    basename = "here_doc_"; //++--++--+-+-+-+--+";
    count = 0;
    strnum = ft_itoa(count);
    if (!strnum)
        return (NULL);
    
    filename = ft_strjoin(basename, strnum);
    free(strnum);
    if (!filename)
        return (NULL);

    while (access(filename, F_OK) == 0)
    {
        count++;
        free(filename);
        strnum = ft_itoa(count);
        printf("01 strnum: %s\n", strnum);
        if (!strnum)
            return (NULL);
        filename = ft_strjoin(basename, strnum);
        printf("02 filename: %s\n", filename);
        free(strnum);
        if (!filename)
            return (NULL);
    }
    //fd_heredoc = open(filename, O_RDWR | O_CREAT, 0666);
    //close(fd_heredoc);
    return (filename);
}

int has_heredoc(t_strcmd *str_cmd, t_shell *shell)
{
    int i;

    i = 0;
    while (str_cmd->redin[i])
    {
        if (is_red(str_cmd->redin[i]) == HEREDOC)
            return (1);
        i++;
    }
    return (0);
}

void red_in(t_strcmd *str_cmd, t_shell *shell, char *here_doc)
{
    char **redin;
    redin = str_cmd->redin;
    int i = 0;
    int index_fd = 0;
    int *fd_infile;
    char *line;

    printf("%s*****\n\n", here_doc);

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
            if (!here_doc)
            {
                /////freeeeee
                return;////////////////////
            }
            i++;
            fd_infile[index_fd] = open(here_doc, O_RDWR | O_CREAT, 0666);
            if (fd_infile[index_fd] < 0)
            {
                perror(here_doc);
                close_fds(fd_infile, i);
                free(fd_infile);
                return ;
            }
            write(STDOUT_FILENO, "> ", 2);
            line = get_next_line(STDIN_FILENO);
            while (!(ft_strncmp(line, redin[i], ft_strlen(redin[i])) == 0 && line[ft_strlen(redin[i])] == '\n'))
            {
                write(fd_infile[index_fd], line, ft_strlen(line));
                free(line);
                write(STDOUT_FILENO, "> ", 2);
                line = get_next_line(STDIN_FILENO);
            }
            free(line);
            close(fd_infile[index_fd]);
            if (index_fd != str_cmd->num_redin - 1)
                unlink(here_doc);
            
            fd_infile[index_fd] = open(here_doc, O_RDONLY, 0666);
            if (fd_infile[index_fd] < 0)
            {
                perror(here_doc);
                close_fds(fd_infile, i);
                free(fd_infile);
                return ;
            }
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
        i++;
        index_fd++;
    }
    dup2(fd_outfile[index_fd - 1], STDOUT_FILENO);
    close(fd_outfile[index_fd - 1]);
    free(fd_outfile);    
}

// void    exec_cmd(t_strcmd *str_cmd, t_shell *shell)
// {
//     red_in(str_cmd, shell);
//     red_out(str_cmd, shell);
// }