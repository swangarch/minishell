/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:09:16 by yfan              #+#    #+#             */
/*   Updated: 2024/10/29 18:09:18 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_default_env(char **env, char *get_path)
{
	env[0] = ft_strdup("USER=guest");
	env[1] = ft_strdup(DEFAULT_PATH);
	env[2] = ft_strjoin("PWD=", get_path);
	env[3] = ft_strdup("SHLVL=1");
	env[4] = ft_strdup("_=/usr/bin/env");
	env[5] = NULL;
}

void	init_no_env(t_shell *shell)
{
	char	*get_path;
	char	**env;

	get_path = getcwd(NULL, 0);
	if (!get_path)
	{
		ft_putstr_fd(MES_CUR_PATH_ERR, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	env = (char **)malloc(6 * sizeof(char *));
	if (!env)
	{
		free(get_path);
		exit(EXIT_FAILURE);
	}
	set_default_env(env, get_path);
	if (env[0] && env[1] && env[2] && env[3] && env[4])
		shell->env_head = init_default_env(env);
	free_env_path(env, get_path);
	if (!shell->env_head)
		exit(EXIT_FAILURE);
}

void	init_shell(t_shell *shell, char **env)
{
	if (!getenv("USER") || !getenv("PATH"))
		init_no_env(shell);
	else
	{
		shell->env_head = init_default_env(env);
		if (!shell->env_head)
			exit(EXIT_FAILURE);
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
}
