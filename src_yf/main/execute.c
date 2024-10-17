#include "../includes/minishell.h"

// void    exec_cmd(t_strcmd *str_cmd, t_shell *shell)
// {
//     red_in(str_cmd, shell);
//     red_out(str_cmd, shell);
// }

void mini_execute(t_shell *shell, t_strcmd *str_cmd)
{
    int i;
    int j;
    int type_cmd;
    pid_t pid;
    int *p_fd;

    // exec_cmd(str_cmd, shell);
    i = 0;
    if (str_cmd->num_cmd == 1)
    {
        type_cmd = is_build_in(str_cmd->tab_cmd[0][0]);
        if (type_cmd)
        {
            red_in(str_cmd, shell);
            red_out(str_cmd, shell);
            g_status = mini_builtin(type_cmd, shell, str_cmd);
            if (access("here_doc", F_OK) == 0)
                unlink("here_doc");
        }
        else
        {
            pid = fork();
            if (pid == -1)
            {
                g_status = 3;
                perror("fork");
                return;
            }
            else if (pid == 0)
            {
                child_signal_handler();
                red_in(str_cmd, shell);
                red_out(str_cmd, shell);
                execute(str_cmd->tab_cmd[i], shell->env);
            }
            signal(SIGINT, SIG_IGN);
            signal(SIGQUIT, SIG_IGN);
            if (access("here_doc", F_OK) == 0)
                unlink("here_doc");
            waitpid(pid, &g_status, 0);
            if ((g_status & 0xFF) == SIGINT)
                write(STDOUT_FILENO, "\n", 1);
        }
        return;
    }
    p_fd = (int *)malloc(2 * (str_cmd->num_cmd - 1) * sizeof(int));
    if (!p_fd)
    {
        g_status = 1;
        ft_putstr_fd(MES_MALLOC_ERR, STDERR_FILENO);
        return;
    }
    while (i < str_cmd->num_cmd - 1)
    {
        if (pipe(p_fd + i * 2) == -1)
        {
            g_status = 2;
            perror(SHELL "pipe failed");
            free(p_fd);
            return;
        }
        ++i;
    }
    i = 0;
    while (i < str_cmd->num_cmd)
    {
        pid = fork();
        if (pid == -1)
        {
            g_status = 3;
            perror(SHELL "fork");
            free(p_fd);
            return;
        }
        else if (pid == 0)
        {
            child_signal_handler();
            if (i > 0)
            {
                dup2(p_fd[(i - 1) * 2], 0);
            }
            if (i < str_cmd->num_cmd - 1)
            {
                dup2(p_fd[i * 2 + 1], 1);
            }
            if (i == 0)
            {
                red_in(str_cmd, shell);
            }
            if (i == str_cmd->num_cmd - 1)
            {
                red_out(str_cmd, shell);
            }
            j = 0;
            while (j < 2 * (str_cmd->num_cmd - 1))
            {
                close(p_fd[j++]);
            }
            execute(str_cmd->tab_cmd[i], shell->env);
        }
        ++i;
    }
    signal(SIGINT, SIG_IGN);  // ！！！！！！！！！！！1
    signal(SIGQUIT, SIG_IGN); // ！！！！！！！！！！！
    j = 0;
    while (j < 2 * (str_cmd->num_cmd - 1))
    {
        close(p_fd[j++]);
    }
    j = 0;
    while (j < str_cmd->num_cmd)
    {
        waitpid(-1, &g_status, 0);
        j++;
        // if ((g_status & 0xFF) == SIGINT)
        //     write(STDOUT_FILENO, "\n", 1);
    }
    if ((g_status & 0xFF) == SIGINT)
        write(STDOUT_FILENO, "\n", 1);
    //检查g_status是否太大超出某个范围！！！处理逻辑是什么？？
    if (access("here_doc", F_OK) == 0)
        unlink("here_doc");
    free(p_fd);
    // signal(SIGINT, handle_sigint);//！！！！！！！！！！1
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
        ft_putstr_fd(SHELL "Command not found: ", 2);
        ft_putstr_fd(cmd[0], 2);
        ft_putstr_fd("\n", 2);
        exit(127);
    }
    if (stat(path, &cmd_stat) == 0 && (cmd_stat.st_mode & S_IFMT) == S_IFDIR)
    {
        ft_putstr_fd(SHELL, STDERR_FILENO);
        ft_putstr_fd(path, STDERR_FILENO);
        ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
        free(path);
        exit(126);
    }
    if (execve(path, cmd, env) == -1)
    {
        free(path);
        perror(SHELL "execve");
        exit(126);
    }
    free(path);
}

char *get_path(char *cmd, char **env)
{
    int i;
    char *part_path;
    char *full_path;
    char **all_path;

    i = -1;
    if (access(cmd, F_OK | X_OK) == 0)
    //如果$HOME作为命令传过来，需要多一步判断不是文件夹
        return (cmd);
    all_path = env_split(env);
    if (!all_path)
        return (NULL);
    while (all_path[++i])
    {
        part_path = ft_strjoin(all_path[i], "/");
        if (!part_path)
            return (free_char_array(all_path), NULL);
        full_path = ft_strjoin(part_path, cmd);
        if (!full_path)
            return (free_char_array(all_path), free(part_path), NULL);
        free(part_path);
        if (access(full_path, F_OK | X_OK) == 0)
            return (free_char_array(all_path), full_path);
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
    if (!i)
        return (NULL);
    all_path = ft_split(env[i] + 5, ':');
    if (!all_path)
        return (NULL);
    return (all_path);
}
