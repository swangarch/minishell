#include "../../includes/minishell.h"

void    init_no_env(t_shell *shell, char ***env)
{
    char    *get_path;

    shell->envless = TRUE;
    shell->color_codes = FALSE;
    shell->cmd_paths = NULL;
    get_path = getcwd(NULL, 0);
    if (!get_path)
    {
        printf(RED MES_CUR_PATH_ERR COLOR_E);
        exit(EXIT_FAILURE);
    }
    if (!(*env))
    {
        *env = (char **)malloc(4 * sizeof(char *));
        if (!(*env))
        {
            printf(RED MES_MALLOC_ERR COLOR_E);
            exit(EXIT_FAILURE);
        }
    }
    (*env)[0] = ft_strjoin("PWD=", get_path);
    if (!((*env)[0]))
    {
        free(*env);
        *env = NULL;
        printf(RED MES_MALLOC_ERR COLOR_E);
        exit(EXIT_FAILURE);
    }
    (*env)[1] = ft_strdup("SHLVL=1");
    if (!((*env)[1]))
    {
        free((*env)[0]);
        free(*env);
        *env = NULL;
        printf(RED MES_MALLOC_ERR COLOR_E);
        exit(EXIT_FAILURE);
    }
    (*env)[2] = ft_strdup("_=/usr/bin/env");
    (*env)[3] = NULL;
    free(get_path);
    shell->env_head = init_default_env(*env);
    if (!shell->env_head)
    {
        free((*env)[0]);
        free((*env)[1]);
        free(*env);
        *env = NULL;
        printf(RED MES_CREAT_NODE COLOR_E);
        exit(EXIT_FAILURE);
    }
}

void    init_shell(t_shell *shell, char **env)
{
    if (!getenv("USER") || !getenv("PATH"))
        init_no_env(shell, &env);
    else
    {
        shell->envless = FALSE;
        shell->color_codes = TRUE;
        shell->env_head = init_default_env(env);
        if (!shell->env_head)
        {
            printf(RED MES_CREAT_NODE COLOR_E);
            exit(EXIT_FAILURE);
        }
        shell->user_name = getenv("USER");
        shell->cmd_paths = ft_split(get_path(env), ':');
        if (!shell->cmd_paths)
        {
            printf(RED MES_PATH_ERR COLOR_E);
            exit(EXIT_FAILURE);
        }
    }
    shell->env = NULL;
    shell->prompt = NULL;
	shell->exit_code = 0;
	shell->print = FALSE;
	shell->heredoc = NULL;
	shell->cmd_tbls = NULL;
	shell->prev_prompt = NULL;
	shell->trimmed_prompt = NULL;
	shell->terminal_prompt = NULL;
	shell->cmd_has_been_executed = TRUE;
	shell->std_fds[0] = dup(STDIN_FILENO);//保护！！！！
	shell->std_fds[1] = dup(STDOUT_FILENO);
    //print_env(shell->env_head);
}

char	*get_path(char **env)
{
	int	index;

	index = 0;
	while (env[index] != NULL)
	{
		if (ft_strncmp(env[index], "PATH=", 5) == 0)
			return (env[index] + 5);
		index++;
	}
	return (NULL);
}

// void    print_env(t_env *head)
// {
//     if (!head)
//     {
//         return ;
//     }
//     while (head)
//     {
//         printf(GREEN "%s" COLOR_E "\n", head->var_name);
//         printf(YELLOW "%s" COLOR_E "\n", head->content);
//         head = head->next;
//     }
// }
