#include "../includes/minishell.h"

void expand_tab(char **tab, t_env *env_head, int status)
{
    int i;

    if (!tab)
        return;
    i = 0;
    while (tab[i])
    {
        tab[i] = expand_tilde(tab[i], env_head);
        tab[i] = expand_var(tab[i], env_head, status);
        i++;
    }
}

void expand_str_cmd(t_cmd **tab_cmd, t_env *env_head, int status)
{
    int i;

    if (!tab_cmd)
        return;
    i = 0;
    while (tab_cmd[i])
    {
        expand_tab(tab_cmd[i]->cmd, env_head, status);
        expand_tab(tab_cmd[i]->redin, env_head, status);
        expand_tab(tab_cmd[i]->redout, env_head, status);
        i++;
    }
}

static int     handle_null_prompt()
{
    if (!errno)
        write(2, "exit\n", 5);
    else
        perror("minishell: Error reading input");
    return (1);
}

static int     read_and_process_input(t_shell *shell)
{
    errno = 0;
    shell->terminal_prompt = join_prompt();
    shell->prompt = readline(shell->terminal_prompt);
    if (!shell->prompt)
        return (handle_null_prompt());
    if (!g_sigint_flag)
    {
        shell->trimmed_prompt = ft_strtrim(shell->prompt, SPACES);
        if (!shell->trimmed_prompt)
            return (free_2_char(shell->terminal_prompt, shell->prompt), 2);
        if (ft_strlen(shell->trimmed_prompt))
            add_history(shell->prompt);
        update_env(shell);
    }
    return 0;
}

static void    execute_commands(t_shell *shell)
{
    if (!g_sigint_flag && lexer(shell))
    {
        shell->tab_cmd = parse_line(shell->trimmed_prompt);
        expand_str_cmd(shell->tab_cmd, shell->env_head, shell->status);
        mini_execute(shell, shell->tab_cmd);
    }
    if (g_sigint_flag)
        shell->status = 130;
}

static void    post_execution_cleanup(t_shell *shell)
{
    g_sigint_flag = FALSE;
    rl_done = 0;
    free_in_loop(shell);
    delete_heredoc(shell->here_docs);
    shell->here_docs = NULL;
}

void minishell_loop(t_shell *shell)
{
    int     flag;
    configure_terminal(&shell->termios_set);
    while (1)
    {
        set_signal_handler();
        flag = read_and_process_input(shell);
        if (flag == 1)
            break;
        else if (flag == 2)
            continue ;
        execute_commands(shell);
        post_execution_cleanup(shell);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &shell->termios_set);
}
