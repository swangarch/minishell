#include "../includes/minishell.h"

void    init_no_env(t_shell *shell)
{
    char    *get_path;
    char    **env;

    get_path = getcwd(NULL, 0);
    if (!get_path)
    {
        ft_putstr_fd(MES_CUR_PATH_ERR, STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    env = (char **)malloc(5 * sizeof(char *));
    if (!env)
    {
        ft_putstr_fd(MES_MALLOC_ERR "case 3", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    env[0] = ft_strdup("USER=guest");
    env[1] = ft_strjoin("PWD=", get_path);
    env[2] = ft_strdup("SHLVL=1");
    env[3] = ft_strdup("_=/usr/bin/env");
    env[4] = NULL;
    if (env[0] && env[1] && env[2] && env[3])
        shell->env_head = init_default_env(env);
    free_env_path(env, get_path);
    if (!shell->env_head)
    {
        ft_putstr_fd(MES_CREAT_NODE, STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
}

void    init_shell(t_shell *shell, char **env)
{
    if (!getenv("USER") || !getenv("PATH"))
        init_no_env(shell);
    else
    {
        shell->env_head = init_default_env(env);
        if (!shell->env_head)
        {
            ft_putstr_fd(MES_CREAT_NODE, STDERR_FILENO);
            exit(EXIT_FAILURE);
        }
    }
    shell->status = 0;
    shell->env = NULL;
    shell->prompt = NULL;
	shell->trimmed_prompt = NULL;
	shell->terminal_prompt = NULL;
    shell->tab_cmd = NULL;
    shell->here_docs = NULL;
	shell->std_fds[0] = dup(STDIN_FILENO);
	shell->std_fds[1] = dup(STDOUT_FILENO);
    if (shell->std_fds[0] == -1 || shell->std_fds[1] == -1)
    {
        perror(MES_DUP_ERR);
        exit(EXIT_FAILURE);
    }
    //print_env(shell->env_head);
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
