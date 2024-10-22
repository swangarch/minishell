#include "../includes/minishell.h"

void    expand_tab(char **tab, t_env *env_head, int status)
{
    int i;

    if (!tab)
        return ;
    i = 0;
    while (tab[i])
    {
        tab[i] = expand_tilde(tab[i], env_head);
        tab[i] = expand_var(tab[i], env_head, status);
        i++;
    }
}

// void    expand_str_cmd(t_cmd **tab_cmd, t_env *env_head)
// {
//     int i = 0;

//     if (!str_cmd)
//         return ;
//     expand_tab(str_cmd->redin, env_head);
//     expand_tab(str_cmd->redout, env_head);
//     while (str_cmd->tab_cmd[i])
//     {
//         expand_tab(str_cmd->tab_cmd[i], env_head);
//         i++;
//     }
// }

void    expand_str_cmd(t_cmd **tab_cmd, t_env *env_head, int status)
{
    int i;

    if (!tab_cmd)
        return ;
    i = 0;
    while (tab_cmd[i])
    {
        expand_tab(tab_cmd[i]->cmd, env_head, status);
        expand_tab(tab_cmd[i]->redin, env_head, status);
        expand_tab(tab_cmd[i]->redout, env_head, status);
        i++;
    }
}

void    minishell_loop(t_shell *shell)
{
    configure_terminal(&shell->termios_set);
    while (1)
    {
        set_signal_handler();
        free_in_loop(shell);
        errno = 0;
        shell->terminal_prompt = join_prompt();
        shell->prompt = readline(shell->terminal_prompt);
        if (g_sigint_flag)
        {
            g_sigint_flag = FALSE;
            shell->status = 130;
        }
        if (!shell->prompt)
        {
            if (!errno)
            {
                write(2, "exit\n", 5);
                break ;
            }
            else
            {
                perror("Error reading input");
                break ;
            }
        }
        shell->trimmed_prompt = ft_strtrim(shell->prompt, SPACES);
        if (ft_strlen(shell->trimmed_prompt))
            add_history(shell->prompt);
        update_env(shell);
        if (lexer(shell))
        {
            shell->tab_cmd = parse_line(shell->trimmed_prompt);//最后再检查free!!!
            expand_str_cmd(shell->tab_cmd, shell->env_head, shell->status);
            mini_execute(shell, shell->tab_cmd);//里面需要free shell->here_docs
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &shell->termios_set);
}
