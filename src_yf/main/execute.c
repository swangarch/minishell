#include "../includes/minishell.h"

void mini_execute(t_shell *shell, t_cmd **tab_cmd)
{
    int i;
    int j;
    int type_cmd;
    pid_t pid;
    int *p_fd;
    char **here_docs; //++++++++++++++++++++++
    int num_cmd;      //++++++++++++++++++++++

    if (!tab_cmd || !shell)
    {
        shell->status = 2;
        return;
    }
    num_cmd = get_cmdtab_num(tab_cmd); //++++++++++++++++++++++
    here_docs = process_heredocs(tab_cmd, shell);
    if (!here_docs)
        return;
    i = 0;
    if (num_cmd == 1)
    {
        type_cmd = is_build_in(tab_cmd[0]->cmd[0]);
        if (type_cmd)
        {
            red_in(tab_cmd[0], shell, i, here_docs);
            red_out(tab_cmd[0], shell);
            shell->status = mini_builtin(type_cmd, shell, tab_cmd, 0);
            delete_heredoc(here_docs);
            dup2(shell->std_fds[0], STDIN_FILENO);
            dup2(shell->std_fds[1], STDOUT_FILENO);
            return;
        }
    }
    p_fd = (int *)malloc(2 * (num_cmd - 1) * sizeof(int));
    if (!p_fd)
    {
        shell->status = 1;
        ft_putstr_fd(MES_MALLOC_ERR, STDERR_FILENO);
        return;
    }
    while (i < num_cmd - 1)
    {
        if (pipe(p_fd + i * 2) == -1)
        {
            shell->status = 2;
            perror("pipe failed");
            free(p_fd);
            return;
        }
        ++i;
    }
    i = 0;
    while (i < num_cmd)
    {
        type_cmd = is_build_in(tab_cmd[i]->cmd[0]);
        pid = fork();
        if (pid == -1)
        {
            shell->status = 3;
            perror(SHELL "fork");
            free(p_fd);
            return;
        }
        else if (pid == 0)
        {
            // child_signal_handler();
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            if (i > 0)
            {
                dup2(p_fd[(i - 1) * 2], 0);
            }
            if (i < num_cmd - 1)
            {
                dup2(p_fd[i * 2 + 1], 1);
            }
            red_in(tab_cmd[i], shell, i, here_docs);
            red_out(tab_cmd[i], shell);
            j = 0;
            while (j < 2 * (num_cmd - 1))
            {
                close(p_fd[j++]);
            }
            if (type_cmd)
            {
                shell->status = mini_builtin(type_cmd, shell, tab_cmd, i);
                exit(shell->status);
            }
            execute(tab_cmd[i]->cmd, shell->env);
        }
        ++i;
    }
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    j = 0;
    while (j < 2 * (num_cmd - 1))
    {
        close(p_fd[j++]);
    }
    j = 0;
    while (j < num_cmd)
    {
        waitpid(-1, &shell->status, 0);
        j++;
    }
    if ((shell->status & 0x7F) != 0) // 低 7 位不为 0 表示信号导致退出
    {
        int term_sig = shell->status & 0x7F; // 提取信号编号
        shell->status = 128 + term_sig;      // 退出状态 = 128 + 信号编号

        if (term_sig == SIGQUIT) // 如果信号编号为 3 (SIGQUIT)
        {
            write(STDOUT_FILENO, "Quit (core dumped)\n", 19); // 输出 SIGQUIT 信息
        }
        if (term_sig == SIGINT)
        {
            write(STDOUT_FILENO, "\n", 1);
        }
    }
    else if ((shell->status & 0x7F) == 0 && ((shell->status >> 8) & 0xFF) != 0) // 正常退出
    {
        shell->status = (shell->status >> 8) & 0xFF; // 提取正常退出状态码
    }
    // if ((shell->status & 0xFF) == SIGINT)
    //     write(STDOUT_FILENO, "\n", 1);
    // else if ((shell->status & 0x7F) == SIGQUIT)  // 低 7 位为信号编号
    // {
    //     write(STDOUT_FILENO, "Quit (core dumped)\n", 19);  // 子进程因 SIGQUIT 退出
    // }
    // else if ((shell->status & 0x7F) == 0 && ((shell->status >> 8) & 0xFF) != 0)  // 正常退出，提取退出状态码
    // {
    //     shell->status = (shell->status >> 8) & 0xFF;
    //     // 处理正常退出
    // }
    // shell->status /= 256;
    delete_heredoc(here_docs);
    free(p_fd);
    //signal(SIGINT, handle_sigint);//！！！！！！！！！！1
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
        ft_putstr_fd("Command not found: ", 2);
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
        perror("execve");
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
    // if (cmd)
    //     ft_putstr_fd(cmd, 1);
    // else
    //     ft_putstr_fd("Pathname is NULL!\n", 1);
    if (access(cmd, F_OK | X_OK) == 0)
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
    if (!i || !env[i])
        return (NULL);
    all_path = ft_split(env[i] + 5, ':');
    if (!all_path)
        return (NULL);
    return (all_path);
}
