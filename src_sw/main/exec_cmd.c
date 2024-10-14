#include "../includes/minishell.h"

void    red_in(t_strcmd *str_cmd, t_shell *shell)
{
    char **redin;
    redin = str_cmd->redin;
    int i = 0;
    int *fd_infile;
    int num_infile;

    while (redin[i])
        i++;
    num_infile = i / 2;
    fd_infile = malloc(num_infile * sizeof(int));

    i = 0;
    while (redin[i])
    {
        if (is_red(redin[i]) == REDIN)
        {
            i++;
            fd_infile[i] = open(redin[i], O_RDONLY);
            if (fd_infile < 0)
            {
                perror("open infile");
                //exit(EXIT_FAILURE);
                return ;//?
            }
        }
        else if (is_red(redin[i]) == HEREDOC)
        {
            char *line;
            i++;
            fd_infile[i] = open("here_doc", O_RDWR | O_CREAT, 0666);
            if (fd_infile < 0)
            {
                perror("here_doc");
                //exit(EXIT_FAILURE);
                return ;//?
            }

            line = get_next_line(STDIN_FILENO);
            while (fd_strcmp(line, redin[i]) != 0)
            {
                write(fd_red)
            }
        }
        i++;
    }

}

void    exec_cmd(t_strcmd str_cmd, t_shell shell)
{
    int fd_in;
    int fd_out;
}