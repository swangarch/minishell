#include "../includes/minishell.h"

static int     handle_single_builtin(t_shell *shell, t_cmd **tab_cmd)
{
    int type_cmd;

    type_cmd = is_build_in(tab_cmd[0]->cmd[0]);
    if (type_cmd)
    {
        if (!red_in(tab_cmd[0], shell, 0) || !red_in(tab_cmd[0], shell, 0))
        {
            delete_heredoc(shell->here_docs);
            shell->here_docs = NULL;
            shell->status = 1;
            return (1);
        }
        shell->status = mini_builtin(type_cmd, shell, tab_cmd, 0);
        delete_heredoc(shell->here_docs);
        shell->here_docs = NULL;
        dup2(shell->std_fds[0], STDIN_FILENO);
        dup2(shell->std_fds[1], STDOUT_FILENO);
        return (1);
    }
    return (0);
}

static int  init_pipe_fds(int **p_fd, int num_cmd, t_shell *shell)
{
    int i;
    *p_fd = malloc(2 * (num_cmd - 1) * sizeof(int));
    if (!*p_fd)
    {
        shell->status = 1;
        return (1);
    }
    i = 0;
    while (i < num_cmd - 1)
    {
        if (pipe(*p_fd + i * 2) == -1)
        {
            shell->status = 2;
            perror(SHELL "pipe");
            free(*p_fd);
            return (1);
        }
        ++i;
    }
    return (0);
}

static void    set_child(int *num, int *p_fd, t_shell *shell, t_cmd *cmd)
{
    int i;
    if (num[1] > 0)
    {
        if (dup2(p_fd[(num[1] - 1) * 2], 0) == -1)
        {
            perror(SHELL "dup2");
            exit(EXIT_FAILURE);
        }
    }
    if (num[1] < num[0] - 1)
    {
        if (dup2(p_fd[num[1] * 2 + 1], 1) == -1)
        {
            perror(SHELL "dup2");
            exit(EXIT_FAILURE);
        }
    }
    if (!red_in(cmd, shell, num[1]) || !red_out(cmd, shell))
        exit(EXIT_FAILURE);
    i = 0;
    while (i < 2 * (num[0] - 1))
        close(p_fd[i++]);
}

static int  cmd_loop(int *num, int *p_fd, t_shell *shell, t_cmd **tab_cmd)
{
    pid_t pid;
    int type_cmd;

    type_cmd = is_build_in(tab_cmd[num[1]]->cmd[0]);
    pid = fork();
    if (pid == -1)
        return (shell->status = 3, perror(SHELL "fork"), free(p_fd), 1);
    else if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        set_child(num, p_fd, shell, tab_cmd[num[1]]);
        if (type_cmd)
        {
            shell->status = mini_builtin(type_cmd, shell, tab_cmd, num[1]);
            exit(shell->status);
        }
        execute(tab_cmd[num[1]]->cmd, shell->env);
    }
    return (0);
}

static void    wait_for_children(int num_cmd, int *p_fd, t_shell *shell)
{
    int term_sig;
    int i;

    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    i = 0;
    while (i < 2 * (num_cmd - 1))
        close(p_fd[i++]);
    i = -1;
    while (++i < num_cmd)
        waitpid(-1, &shell->status, 0);
    if ((shell->status & 0x7F) != 0)
    {
        term_sig = shell->status & 0x7F;
        shell->status = 128 + term_sig;
        if (term_sig == SIGQUIT)
            write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
        if (term_sig == SIGINT)
            write(STDOUT_FILENO, "\n", 1);
    }
    else if ((shell->status & 0x7F) == 0 && ((shell->status >> 8) & 0xFF) != 0)
        shell->status = (shell->status >> 8) & 0xFF;
}

void mini_execute(t_shell *shell, t_cmd **tab_cmd)
{
    int num[2];
    int *p_fd;

    if (!tab_cmd || !shell)
        return (shell->status = 2, (void)0);
    num[0] = get_cmdtab_num(tab_cmd);
    shell->here_docs = process_heredocs(tab_cmd, shell, num[0]);
    if (!shell->here_docs)
        return ;
    if (num[0] == 1 && handle_single_builtin(shell, tab_cmd))
        return ;
    if (init_pipe_fds(&p_fd, num[0], shell))
        return ;
    num[1] = -1;
    while (++(num[1]) < num[0])
        if (cmd_loop(num, p_fd, shell, tab_cmd))
            return ;
    wait_for_children(num[1], p_fd, shell);
    free(p_fd);
    delete_heredoc(shell->here_docs);
    shell->here_docs = NULL;
}

void execute(char **cmd, char **env)
{
    char *path;
    struct stat cmd_stat;

    if (!cmd[0][0])
        exit(0);
    path = get_path(cmd[0], env);
    if (!path)
    {
        ft_put3str_fd(SHELL, cmd[0], COMMAND_NO, STDERR_FILENO);
        exit(127);
    }
    if (stat(path, &cmd_stat) == 0 && (cmd_stat.st_mode & S_IFMT) == S_IFDIR)
    {
        ft_put3str_fd(SHELL, path, MES_IS_DIR, STDERR_FILENO);
        free(path);
        exit(126);
    }
    if (execve(path, cmd, env) == -1)
    {
        free(path);
        perror("execve");
        exit(126);
    }
    free(path);
}

static int     check_path_access(char *cmd)
{
    if (access(cmd, F_OK | X_OK) == 0)
        return (0);
    if (ft_strchr(cmd, '/') && access(cmd, F_OK))
    {
        ft_put3str_fd(SHELL, cmd, MES_CD_ENOENT, STDERR_FILENO);
        exit(127);
    }
    if (ft_strchr(cmd, '/') && access(cmd, X_OK))
    {
        ft_put3str_fd(SHELL, cmd, MES_CD_EACCES, STDERR_FILENO);
        exit(126);
    }
    return (1);
}

static char    *get_full_path(char *cmd, char *path, char **all_path)
{
    char *part_path;
    char *full_path;

    part_path = ft_strjoin(path, "/");
    if (!part_path)
        return (NULL);
    full_path = ft_strjoin(part_path, cmd);
    free(part_path);
    return (full_path);
}

static int     validate_access(char *cmd, char *full_path, char **all_path)
{
    if (access(full_path, F_OK) == 0)
    {
        if (access(full_path, X_OK))
        {
            ft_put3str_fd(SHELL, cmd, MES_CD_EACCES, STDERR_FILENO);
            free_char_array(all_path);
            free(full_path);
            exit(126);
        }
        free_char_array(all_path);
        return (TRUE);
    }
    return (FALSE);
}


char *get_path(char *cmd, char **env)
{
    int i;
    char *full_path;
    char **all_path;

    i = -1;
    if (!check_path_access(cmd))
        return (cmd);
    all_path = env_split(env);
    if (!all_path)
        return (NULL);
    while (all_path[++i])
    {
        full_path = get_full_path(cmd, all_path[i], all_path);
        if (!full_path)
            return (free_char_array(all_path), NULL);
        if (validate_access(cmd, full_path, all_path))
            return (full_path);
        free(full_path);
    }
    return (free_char_array(all_path), NULL);
}

char **env_split(char **env)
{
    int i;
    char **all_path;

    i = 0;
    while (env && env[i] && ft_strnstr(env[i], "PATH", 4) == 0)
        i++;
    if (!i || !env[i])
        return (NULL);
    all_path = ft_split(env[i] + 5, ':');
    if (!all_path)
        return (NULL);
    return (all_path);
}
