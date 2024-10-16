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
        ;//g_status = mini_export();
    else if (type == 5)
        ;//g_status = mini_unset();
    else if (type == 6)
        ;//g_status = mini_env();
    else if (type == 7)
        g_status = mini_exit(shell, cmd);
    return (g_status);
}

int    mini_exit(t_shell *shell, t_strcmd *cmd)
{
    if (count_cmd(cmd->tab_cmd[0]) != 1)
    {
        ft_putstr_fd(MES_EXIT_ERR, STDERR_FILENO);
        return (2);
    }
    else
    {
        ft_putstr_fd("exit\n", STDERR_FILENO);
        free_before_exit(shell);//free cmd aussi!
        exit(EXIT_SUCCESS);
    }
}
