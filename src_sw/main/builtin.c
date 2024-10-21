#include "../includes/minishell.h"

int     mini_builtin(int type, t_shell *shell, t_strcmd *cmd)
{
    if (type == 1)
        ;//g_status = mini_echo();
    else if (type == 2)
        ;//g_status = mini_cd();
    else if (type == 3)
        ;//g_status = mini_pwd();
    else if (type == 4)
        g_status = mini_export(&shell->env_head, cmd->tab_cmd[0]);
    else if (type == 5)
        g_status = mini_unset(&shell->env_head, cmd->tab_cmd[0]);
    else if (type == 6)
        g_status = mini_env(shell->env, cmd);
    else if (type == 7)
        g_status = mini_exit(shell, cmd);
    return (g_status);
}

int    mini_exit(t_shell *shell, t_strcmd *cmd)
{
    char    **ptr;
    int     i;
    long long   val;

    ptr = cmd->tab_cmd[0];
    i = 1;
    if (ptr[i])
    {
        while (ptr[i])
        {
            if (ptr[i][0] == '-' && !is_numeric(ptr[i]))
            {
                ft_putstr_fd(MES_EXIT_OP, STDERR_FILENO);
                return (2);
            }
            ++i;
        }
        i = 1;
        if (!str_to_ll(ptr[i], &val))
        {
            ft_putstr_fd("exit\n", STDERR_FILENO);
            ft_putstr_fd("exit: ", STDERR_FILENO);
            ft_putstr_fd(ptr[i], STDERR_FILENO);
            ft_putstr_fd(MES_EXIT_NUM, STDERR_FILENO);
            free_before_exit(shell);//free cmd aussi!
            exit (2);
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
    free_before_exit(shell);//free cmd aussi!
    exit(EXIT_SUCCESS);
}

int     mini_env(char **env, t_strcmd *cmd)
{
    int     i;

    if (count_cmd(cmd->tab_cmd[0]) != 1)
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

int     mini_unset(t_env **head, char **cmd)
{
    int     i;

    i = 1;
    if (count_cmd(cmd) == 1)
        return (0);
    while (cmd[i])
    {
        if (cmd[i][0] == '-')
        {
            ft_putstr_fd(MES_ENSET_OP, STDERR_FILENO);
            return (2);
        }
        if (!is_valid_name(cmd[i]))
        {
            ++i;
            continue ;
        }
        unset_var(head, cmd[i]);
        ++i;
    }
    return (0);
}

int     mini_export(t_env **head, char **cmd)
{
    t_env   *current;
    int     i;

    current = *head;
    if (count_cmd(cmd) == 1)
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
    while (cmd[i])
    {
        if (cmd[i][0] == '-')
        {
            ft_putstr_fd(MES_EXPORT_OP, STDERR_FILENO);
            return (2);
        }
    }
    return (0);
}
