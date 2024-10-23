#include "../includes/minishell.h"

int mini_builtin(int type, t_shell *shell, t_cmd **tab_cmd, int i)
{
    if (type == MINI_ECHO)
        shell->status = mini_echo(tab_cmd[i]->cmd);
    else if (type == MINI_CD)
        shell->status = mini_cd(&shell->env_head, tab_cmd[i]->cmd);
    else if (type == MINI_PWD)
        shell->status = mini_pwd(tab_cmd[i]->cmd);
    else if (type == MINI_EXPORT)
        shell->status = mini_export(&shell->env_head, tab_cmd[i]->cmd);
    else if (type == MINI_UNSET)
        shell->status = mini_unset(&shell->env_head, tab_cmd[i]->cmd);
    else if (type == MINI_ENV)
        shell->status = mini_env(shell->env, tab_cmd, i);
    else if (type == MINI_EXIT)
        shell->status = mini_exit(shell, tab_cmd, i);
    return (shell->status);
}

// void update_env_vars(const char *old_pwd, const char *new_pwd)
// {
//     setenv("OLDPWD", old_pwd, 1);
//     setenv("PWD", new_pwd, 1);
// }

int mini_cd(t_env **head, char **cmd)
{
    char *dir;
    char *old_pwd;
    char *new_pwd;

    old_pwd = getcwd(NULL, 0);
    if (!old_pwd)
    {
        ft_putstr_fd(MES_CUR_PATH_ERR, STDERR_FILENO);
        return (1);
    }
    if (count_cmd(cmd) > 2)
    {
        ft_putstr_fd(MES_CD_TOO_MANY, STDERR_FILENO);
        return (1);
    }
    if (count_cmd(cmd) == 1)
    {
        dir = mini_get_env("HOME", *head);
        if (!dir[0])
        {
            ft_putstr_fd(MES_CD_HOME, STDERR_FILENO);
            free(old_pwd);
            free(dir);
            return (1);
        }
    }
    else if (!strcmp(cmd[1], "-"))
    {
        dir = mini_get_env("OLDPWD", *head);
        if (!dir[0])
        {
            ft_putstr_fd(MES_CD_OLD, STDERR_FILENO);
            free(old_pwd);
            free(dir);
            return (1);
        }
        ft_putstr_fd(dir, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
    }
    else
    {
        dir = ft_strdup(cmd[1]);
    }
    if (chdir(dir) != 0)
    {
        if (errno == ENOENT)
        {
            ft_putstr_fd(SHELL, STDERR_FILENO);
            ft_putstr_fd("cd: ", STDERR_FILENO);
            ft_putstr_fd(dir, STDERR_FILENO);
            ft_putstr_fd(MES_CD_ENOENT, STDERR_FILENO);
        }
        else if (errno == ENOTDIR)
        {
            ft_putstr_fd(SHELL, STDERR_FILENO);
            ft_putstr_fd("cd: ", STDERR_FILENO);
            ft_putstr_fd(dir, STDERR_FILENO);
            ft_putstr_fd(MES_CD_ENOTDIR, STDERR_FILENO);
        }
        else if (errno == EACCES)
        {
            ft_putstr_fd(SHELL, STDERR_FILENO);
            ft_putstr_fd("cd: ", STDERR_FILENO);
            ft_putstr_fd(dir, STDERR_FILENO);
            ft_putstr_fd(MES_CD_EACCES, STDERR_FILENO);
        }
        else
        {
            ft_putstr_fd(SHELL, STDERR_FILENO);
            ft_putstr_fd("cd: ", STDERR_FILENO);
            ft_putstr_fd(dir, STDERR_FILENO);
            ft_putstr_fd(": ", STDERR_FILENO);
            ft_putstr_fd(strerror(errno), STDERR_FILENO);
            ft_putstr_fd("\n", STDERR_FILENO);
        }
        free(old_pwd);
        free(dir);
        return (1);
    }
    new_pwd = getcwd(NULL, 0);
    if (!new_pwd)
    {
        ft_putstr_fd(MES_CUR_PATH_ERR, STDERR_FILENO);
        free(old_pwd);
        free(dir);
        return (1);
    }
    set_pwd(head, "PWD", new_pwd);
    set_pwd(head, "OLDPWD", old_pwd);
    free(old_pwd);
    free(dir);
    free(new_pwd);
    return (0);
}

int mini_pwd(char **cmd)
{
    char *get_path;

    if (count_cmd(cmd) > 1)
    {
        if (cmd[1][0] == '-' && ft_strcmp(cmd[1], "--"))
        {
            ft_putstr_fd(MES_PWD_OP, STDERR_FILENO);
            return (2);
        }
    }
    get_path = getcwd(NULL, 0);
    if (!get_path)
    {
        ft_putstr_fd(MES_CUR_PATH_ERR, STDERR_FILENO);
        return (1);
    }
    ft_putstr_fd(get_path, STDOUT_FILENO);
    ft_putstr_fd("\n", STDOUT_FILENO);
    free(get_path);
    return (0);
}

int mini_exit(t_shell *shell, t_cmd **tab_cmd, int place)
{
    char **ptr;
    int i;
    long long val;

    ptr = tab_cmd[place]->cmd;
    i = 1;
    if (ptr[i])
    {
        // while (ptr[i])
        // {
        //     if (ptr[i][0] == '-' && !is_numeric(ptr[i]))
        //     {
        //         ft_putstr_fd(MES_EXIT_OP, STDERR_FILENO);
        //         return (2);
        //     }
        //     ++i;
        // }
        // i = 1;
        if (!str_to_ll(ptr[i], &val))
        {
            ft_putstr_fd("exit\n", STDERR_FILENO);
            ft_putstr_fd("exit: ", STDERR_FILENO);
            ft_putstr_fd(ptr[i], STDERR_FILENO);
            ft_putstr_fd(MES_EXIT_NUM, STDERR_FILENO);
            free_before_exit(shell); // free cmd aussi!
            exit(2);
        }
        if (ptr[i + 1])
        {
            ft_putstr_fd("exit\n", STDERR_FILENO);
            ft_putstr_fd(MES_EXIT_TOO_MANY, STDERR_FILENO);
            return (1);
        }
        if (val < 0)
            val = (val % 256 + 256) % 256;
        ft_putstr_fd("exit\n", STDERR_FILENO);
        exit((int)(val % 256));
    }
    ft_putstr_fd("exit\n", STDERR_FILENO);
    free_before_exit(shell); // free tab_cmd aussi!
    exit(EXIT_SUCCESS);
}

int mini_env(char **env, t_cmd **tab_cmd, int place)
{
    int i;

    if (count_cmd(tab_cmd[place]->cmd) != 1)
    {
        ft_putstr_fd(MES_ENV_ERR, STDERR_FILENO);
        return (2);
    }
    i = 0;
    while (env[i])
    {
        printf("%s\n", env[i]);
        ++i;
    }
    return (0);
}

int mini_unset(t_env **head, char **cmd)
{
    int i;

    i = 1;
    if (count_cmd(cmd) == 1)
        return (0);
    if (!ft_strcmp(cmd[1], "--"))
        i = 2;
    while (cmd[i])
    {
        if (cmd[1][0] == '-' && ft_strcmp(cmd[1], "--"))
        {
            ft_putstr_fd(MES_ENSET_OP, STDERR_FILENO);
            return (2);
        }
        if (!is_valid_name(cmd[i]))
        {
            ++i;
            continue;
        }
        unset_var(head, cmd[i]);
        ++i;
    }
    return (0);
}

int mini_export(t_env **head, char **cmd)
{
    t_env *current;
    char **arg;
    int i;
    int invalid_arg;

    current = *head;
    invalid_arg = FALSE;
    if ((count_cmd(cmd) == 1) || (count_cmd(cmd) == 2 && !ft_strcmp(cmd[1], "--")))
    {
        while (current)
        {
            if (ft_strcmp(current->var_name, "_"))
            {
                printf(EXPORT_PRE "%s=%s\n", current->var_name, current->content);
            }
            current = current->next;
        }
        return (0);
    }
    i = 1;
    if (!ft_strcmp(cmd[1], "--"))
        i = 2;
    while (cmd[i])
    {
        if (cmd[1][0] == '-' && ft_strcmp(cmd[1], "--"))
        {
            ft_putstr_fd(MES_EXPORT_OP, STDERR_FILENO);
            return (2);
        }
        arg = split_by_equal(cmd[i]);
        if (!arg)
            return (1);
        if (!is_valid_name(arg[0]))
        {
            invalid_arg = TRUE;
            ft_putstr_fd(MES_EXPORT_ERR, STDERR_FILENO);
            ft_putstr_fd(arg[0], STDERR_FILENO);
            ft_putstr_fd("\n", STDERR_FILENO);
            ++i;
            continue;
        }
        set_var(head, arg, cmd[i]);
        ++i;
    }
    if (invalid_arg)
        return (1);
    return (0);
}

int mini_echo(char **cmd)
{
    int no_newline;
    int valid_n_option;
    int i = 1;
    int j;

    no_newline = FALSE;
    while (cmd[i])
    {
        if (!strncmp(cmd[i], "-n", 2))
        {
            valid_n_option = TRUE;
            j = 2;
            while (cmd[i][j])
            {
                if (cmd[i][j] != 'n')
                {
                    valid_n_option = FALSE;
                    break;
                }
                ++j;
            }
            if (valid_n_option)
            {
                no_newline = TRUE;
                ++i;
                continue;
            }
        }
        break;
    }
    while (cmd[i])
    {
        ft_putstr_fd(cmd[i], STDOUT_FILENO);
        if (cmd[i + 1])
        {
            ft_putstr_fd(" ", STDOUT_FILENO);
        }
        ++i;
    }
    if (!no_newline)
    {
        ft_putstr_fd("\n", STDOUT_FILENO);
    }
    return (0);
}
