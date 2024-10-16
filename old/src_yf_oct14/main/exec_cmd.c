#include "../includes/minishell.h"

// int *red_in(t_strcmd *str_cmd, t_shell *shell)
// {
//     char **redin;
//     redin = str_cmd->redin;
//     int i = 0;
//     int *fd_infile;
//     int num_infile;


//     num_infile = str_cmd->num_redin;
//     fd_infile = malloc(num_infile * sizeof(int));
//     if (!fd_infile)
//         return ;

//     while (redin[i])
//     {
//         if (is_red(redin[i]) == REDIN)
//         {
//             i++;
//             fd_infile[i / 2] = open(redin[i], O_RDONLY);
//             if (fd_infile[i / 2] < 0)
//             {
//                 perror("open infile");
//                 //exit(EXIT_FAILURE);///clear all
//                 return ;//?
//             }
//             dup2(fd_infile[i / 2], STDIN_FILENO);
//         }
//         else if (is_red(redin[i]) == HEREDOC)
//         {
//             char *line;
//             i++;
//             fd_infile[i / 2] = open("here_doc", O_RDWR | O_CREAT, 0666);
//             if (fd_infile[i / 2] < 0)
//             {
//                 perror("here_doc");
//                 //exit(EXIT_FAILURE);clear allv
//                 return ;//?
//             }

//             line = get_next_line(STDIN_FILENO);
//             while (fd_strcmp(line, redin[i]) != 0)
//             {
//                 write(fd_infile[i / 2], line, ft_strlen(line));
//                 free(line);
//                 line = get_next_line(STDIN_FILENO);
//             }
//             free(line);
//             dup2(fd_infile[i / 2], STDIN_FILENO);
//         }
//         i++;
//     }
//     return (fd_infile);
// }

// int *red_out(t_strcmd *str_cmd, t_shell *shell)
// {
//     char **redout;
//     redout = str_cmd->redout;
//     int i = 0;
//     int *fd_outfile;
//     int num_outfile;

//     num_outfile = str_cmd->num_redout;
//     fd_outfile = malloc(num_outfile * sizeof(int));

//     if (!fd_outfile)
//         return ;
//     while (redout[i])
//     {
//         if (is_red(redout[i]) == REDOUT)
//         {
//             i++;
//             fd_outfile[i / 2] = open(redout[i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
//             if (fd_outfile[i / 2] < 0)
//             {
//                 perror("open outfile");
//                 //exit(EXIT_FAILURE);clear all
//                 return ;//?
//             }
//             dup2(fd_outfile[i / 2], STDOUT_FILENO);
//         }
//         else if (is_red(redout[i]) == APPEND)
//         {
//             i++;
//             fd_outfile[i / 2] = open(redout[i], O_CREAT | O_WRONLY | O_APPEND, 0666);
//             if (fd_outfile[i / 2] < 0)
//             {
//                 perror("open outfile");
//                 //exit(EXIT_FAILURE);clear all
//                 return ;//?
//             }
//             dup2(fd_outfile[i / 2], STDOUT_FILENO);
//         }
//         i++;
//     }
//     return (fd_outfile);
// }

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
    int *fd_infile;
    char *line;

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
            fd_infile[i / 2] = open(redin[i], O_RDONLY);
            if (fd_infile[i / 2] < 0)
            {
                perror("open infile");
                close_fds(fd_infile, i);
                free(fd_infile);
                return ;
            }
        }
        else if (is_red(redin[i]) == HEREDOC)
        {
            i++;
            fd_infile[i / 2] = open("here_doc", O_RDWR | O_CREAT, 0666);
            if (fd_infile[i / 2] < 0)
            {
                perror("here_doc");
                close_fds(fd_infile, i);
                free(fd_infile);
                return ;
            }
            line = get_next_line(STDIN_FILENO);
            while (ft_strncmp(line, redin[i], ft_strlen(redin[i])) != 0)
            {
                write(fd_infile[i / 2], line, ft_strlen(line));
                free(line);
                line = get_next_line(STDIN_FILENO);
            }
            free(line);
        }
        dup2(fd_infile[i / 2], STDIN_FILENO);
        close(fd_infile[i / 2]);
        i++;
    }
    free(fd_infile);
}

void red_out(t_strcmd *str_cmd, t_shell *shell)
{
    char **redout;
    redout = str_cmd->redout;
    int i = 0;
    int *fd_outfile;

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
            fd_outfile[i / 2] = open(redout[i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
            if (fd_outfile[i / 2] < 0)
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
            fd_outfile[i / 2] = open(redout[i], O_CREAT | O_WRONLY | O_APPEND, 0666);///Here can be optimized???i++
            if (fd_outfile[i / 2] < 0)
            {
                perror(redout[i]);
                close_fds(fd_outfile, i);
                free(fd_outfile);
                return ;
            }
        }
        dup2(fd_outfile[i / 2], STDOUT_FILENO);
        close(fd_outfile[i / 2]);
        i++;
    }
    free(fd_outfile);    
}

void    exec_cmd(t_strcmd *str_cmd, t_shell *shell)
{
    red_in(str_cmd, shell);
    red_out(str_cmd, shell);
}