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

char    *cd_set_dir(t_env **head, char **cmd)
{
    char    *dir;

    if (count_cmd(cmd) == 1)
    {
        dir = mini_get_env("HOME", *head);
        if (!dir || !dir[0])
        {
            ft_putstr_fd(MES_CD_HOME, STDERR_FILENO);
            return (free(dir), NULL);
        }
    }
    else if (!strcmp(cmd[1], "-"))
    {
        dir = mini_get_env("OLDPWD", *head);
        if (!dir || !dir[0])
        {
            ft_putstr_fd(MES_CD_OLD, STDERR_FILENO);
            return (free(dir), NULL);
        }
        ft_putstr_fd(dir, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
    }
    else
        dir = ft_strdup(cmd[1]);
    return (dir);
}

int     cd_change_dir(char *dir)
{
    if (chdir(dir) != 0)
    {
        if (errno == ENOENT)
            ft_put3str_fd(SHELL "cd: ", dir, \
                MES_CD_ENOENT, STDERR_FILENO);
        else if (errno == ENOTDIR)
            ft_put3str_fd(SHELL "cd: ", dir, \
                MES_CD_ENOTDIR, STDERR_FILENO);
        else if (errno == EACCES)
            ft_put3str_fd(SHELL "cd: ", dir, \
                MES_CD_EACCES, STDERR_FILENO);
        else
        {
            ft_put3str_fd(SHELL "cd: ", dir, ": ", STDERR_FILENO);
            ft_putstr_fd(strerror(errno), STDERR_FILENO);
            ft_putstr_fd("\n", STDERR_FILENO);
        }
        return (1);
    }
    return (0);
}

int mini_cd(t_env **head, char **cmd)
{
    char *dir;
    char *old_pwd;
    char *new_pwd;

    if (!head)
        return (1);
    old_pwd = getcwd(NULL, 0);
    if (!old_pwd)
        return (ft_putstr_fd(MES_CUR_PATH_ERR, STDERR_FILENO), 1);
    if (count_cmd(cmd) > 2)
        return (ft_putstr_fd(MES_CD_TOO_MANY, STDERR_FILENO), \
            free(old_pwd), 1);
    dir = cd_set_dir(head, cmd);
    if (!dir)
        return (free(old_pwd), 1);
    if (cd_change_dir(dir))
        return (free(old_pwd), free(dir), 1);
    new_pwd = getcwd(NULL, 0);
    if (!new_pwd)
        return (ft_putstr_fd(MES_CUR_PATH_ERR, STDERR_FILENO), \
            free(old_pwd), free(dir), 1);
    set_pwd(head, "PWD", new_pwd);
    set_pwd(head, "OLDPWD", old_pwd);
    return (free(old_pwd), free(dir), free(new_pwd), 0);
}

int mini_pwd(char **cmd)
{
    char *get_path;

    if (count_cmd(cmd) > 1)
    {
        if (cmd[1][0] == '-' && ft_strcmp(cmd[1], "-") && ft_strcmp(cmd[1], "--"))
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
    int i;
    long long val;

    i = 1;
    if (tab_cmd[place]->cmd[i])
    {
        if (!str_to_ll(tab_cmd[place]->cmd[i], &val))
        {
            ft_putstr_fd("exit\n", STDERR_FILENO);
            ft_put3str_fd("minishell: exit: ", tab_cmd[place]->cmd[i], \
                MES_EXIT_NUM, STDERR_FILENO);
            free_before_exit(shell);
            exit(2);
        }
        if (tab_cmd[place]->cmd[i + 1])
            return (ft_put3str_fd("exit\n", MES_EXIT_TOO_MANY, NULL, STDERR_FILENO), 1);
        if (val < 0)
            val = (val % 256 + 256) % 256;
        ft_putstr_fd("exit\n", STDERR_FILENO);
        exit((int)(val % 256));
    }
    ft_putstr_fd("exit\n", STDERR_FILENO);
    free_before_exit(shell);
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

    if (!head)
        return (1);
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

int     export_set_var(t_env **head, char **cmd, int i, int *inval)
{
    char    **arg;

    while (cmd[i])
    {
        if (cmd[1][0] == '-' && ft_strcmp(cmd[1], "-") && ft_strcmp(cmd[1], "--"))
            return (ft_putstr_fd(MES_EXPORT_OP, STDERR_FILENO), 2);
        arg = split_by_equal(cmd[i]);
        if (!arg)
            return (1);
        if (!is_valid_name(arg[0]))
        {
            *inval = TRUE;
            ft_put3str_fd(MES_EXP_PRE, cmd[i], MES_EXP_POST, STDERR_FILENO);
            ++i;
            continue;
        }
        set_var(head, arg, cmd[i]);
        free_char_array(arg);
        ++i;
    }
    return (0);
}

void    export_print(t_env *current)
{
    while (current)
    {
        if (ft_strcmp(current->var_name, "_"))
            printf(EXPORT_PRE "%s=%s\n", current->var_name, current->content);
        current = current->next;
    }
}

int mini_export(t_env **head, char **cmd)
{
    t_env *current;
    int val;
    int i;
    int invalid_arg;

    if (!head)
        return (1);
    current = *head;
    invalid_arg = FALSE;
    if ((count_cmd(cmd) == 1) || (count_cmd(cmd) == 2 && !ft_strcmp(cmd[1], "--")))
    {
        export_print(current);
        return (0);
    }
    i = 1;
    if (!ft_strcmp(cmd[1], "--"))
        i = 2;
    val = export_set_var(head, cmd, i, &invalid_arg);
    if (val)
        return (val);
    if (invalid_arg)
        return (1);
    return (0);
}

void    echo_check_newline(char **cmd, int *info)
{
    while (cmd[info[2]])
    {
        if (!strncmp(cmd[info[2]], "-n", 2))
        {
            info[1] = TRUE;
            info[3] = 2;
            while (cmd[info[2]][info[3]])
            {
                if (cmd[info[2]][info[3]] != 'n')
                {
                    info[1] = FALSE;
                    break;
                }
                ++info[3];
            }
            if (info[1])
            {
                info[0] = TRUE;
                ++info[2];
                continue;
            }
        }
        break;
    }
}

int mini_echo(char **cmd)
{
    int     info[4];

    info[0] = FALSE;
    info[2] = 1;
    echo_check_newline(cmd, info);
    while (cmd[info[2]])
    {
        ft_putstr_fd(cmd[info[2]], STDOUT_FILENO);
        if (cmd[info[2] + 1])
        {
            ft_putstr_fd(" ", STDOUT_FILENO);
        }
        ++info[2];
    }
    if (!info[0])
        ft_putstr_fd("\n", STDOUT_FILENO);
    return (0);
}
