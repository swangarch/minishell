#include "../../includes/minishell.h"

void    minishell_loop(t_shell *shell)
{
    configure_terminal();
    while (1)
    {
        set_signal_handler();
        errno = 0;
        set_prompt(shell);//check NULL!!!
        shell->prompt = readline(shell->terminal_prompt);
        if (!shell->prompt)
        {
            if (!errno)
                break ;
            // else
            // {
            //     perror("Error reading input");
            //     continue ;
            // }
        }
        shell->trimmed_prompt = ft_strtrim(shell->prompt, SPACES);
        if (ft_strlen(shell->trimmed_prompt))
            add_history(shell->prompt);
        //update_env(shell);
        // for (int i = 0; shell->env[i]; ++i)
        // {
        //     printf(RED "%s" COLOR_E "\n", shell->env[i]);
        // }
        if (lexer(shell))//parser(shell)
        {
            shell->trimmed_prompt = expand_var(shell->trimmed_prompt, shell->env_head);
            printf("%s\n", shell->trimmed_prompt);
            //execute(shell, shell->cmd_tbls);
        }
        free(shell->prompt);
        free(shell->trimmed_prompt);
    }
}

// void	update_env(t_shell *shell)
// {
// 	if (shell->env != NULL)
// 		free_char_array(shell->env);
// 	shell->env = env_list_to_char(shell->env_head);
// }
