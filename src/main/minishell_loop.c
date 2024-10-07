#include "../../includes/minishell.h"

void    minishell_loop(t_shell *shell)
{
    configure_terminal(&shell->mirror_termios);
    while (1)
    {
        set_signal_handler();
        if (g_ctrl_c)
        {
            g_ctrl_c = 0;
            // if (shell->prompt)
            // {
            //     free(shell->prompt);
            //     shell->prompt = NULL;
            // }
            continue ;
        }
        errno = 0;
        set_prompt(shell);//check NULL!!!
        shell->prompt = readline(shell->terminal_prompt);
        if (!shell->prompt)
        {
            if (!errno)
            {
                break ;
            }
            else
            {
                perror("Error reading input");
                continue ;
            }
        }
        shell->trimmed_prompt = ft_strtrim(shell->prompt, SPACES);
        update_env(shell);
        // for (int i = 0; shell->env[i]; ++i)
        // {
        //     printf(RED "%s" COLOR_E "\n", shell->env[i]);
        // }
        if (lexer(shell))//parser(shell)
        {
            //execute(shell, shell->cmd_tbls);
        }
        ft_add_history(shell);
    }
}

void	update_env(t_shell *shell)
{
	if (shell->env != NULL)
		free_char_array(shell->env);
	shell->env = env_list_to_char(shell->env_head);
}
