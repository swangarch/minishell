#include "../includes/minishell.h"

void    expand_tab(char **tab, t_env *env_head)
{
    int i = 0;

    if (!tab)
        return ;
    while (tab[i])
    {
        tab[i] = expand_tilde(tab[i], env_head);
        tab[i] = expand_var(tab[i], env_head);
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

void    expand_str_cmd(t_cmd **tab_cmd, t_env *env_head)
{
    int i = 0;

    if (!tab_cmd)
        return ;
    while (tab_cmd[i])
    {
        expand_tab(tab_cmd[i]->cmd, env_head);
        expand_tab(tab_cmd[i]->redin, env_head);
        expand_tab(tab_cmd[i]->redout, env_head);
        i++;
    }
}

void    minishell_loop(t_shell *shell)
{
    t_cmd	**tab_cmd;

    configure_terminal(&shell->termios_set);
    while (1)
    {
        set_signal_handler();
        errno = 0;
        set_prompt(shell);//check NULL!!!
        shell->prompt = readline(shell->terminal_prompt);
        if (!shell->prompt)
        {
            if (!errno)
            {
                write(2, "exit\n", 5);
                break ;
            }
            // else
            // {
            //     perror("Error reading input");
            //     continue ;
            // }
        }
        shell->trimmed_prompt = ft_strtrim(shell->prompt, SPACES);
        //printf("Trimmed prompt: '%s'\n", shell->trimmed_prompt);
        if (ft_strlen(shell->trimmed_prompt))
            add_history(shell->prompt);
        update_env(shell);
        // for (int i = 0; shell->env[i]; ++i)
        // {
        //     printf(RED "%s" COLOR_E "\n", shell->env[i]);
        // }
        if (lexer(shell))//parser(shell)
        {
            //shell->trimmed_prompt = expand_var(shell->trimmed_prompt, shell->env_head);
            //printf("%s\n", shell->trimmed_prompt);

            tab_cmd = parse_line(shell->trimmed_prompt);
            expand_str_cmd(tab_cmd, shell->env_head);
            //write(1, "\n\n", 2);
            //print_token_str(str_cmd);
            //printf("expansion done\n");
            mini_execute(shell, tab_cmd);
        }
        free(shell->prompt);
        free(shell->trimmed_prompt);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &shell->termios_set);
}

void	update_env(t_shell *shell)
{
	if (shell->env != NULL)
		free_char_array(shell->env);
	shell->env = env_list_to_char(shell->env_head);
}
