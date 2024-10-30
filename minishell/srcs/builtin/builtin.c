/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:27:15 by yfan              #+#    #+#             */
/*   Updated: 2024/10/29 12:27:18 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mini_builtin(int type, t_shell *shell, t_cmd **tab_cmd, int i)
{
	if (type == MINI_ECHO)
		shell->status = mini_echo(tab_cmd[i]->cmd);
	else if (type == MINI_CD)
		shell->status = mini_cd(&shell->env_head, tab_cmd[i]->cmd);
	else if (type == MINI_PWD)
		shell->status = mini_pwd(tab_cmd[i]->cmd);
	else if (type == MINI_EXPORT)
		shell->status = mini_export(&shell->env_head, tab_cmd[i]->cmd);
	else if (type == MINI_UNSET)
		shell->status = mini_unset(&shell->env_head, tab_cmd[i]->cmd);
	else if (type == MINI_ENV)
		shell->status = mini_env(shell->env, tab_cmd, i);
	else if (type == MINI_EXIT)
		shell->status = mini_exit(shell, tab_cmd, i);
	return (shell->status);
}

int	mini_pwd(char **cmd)
{
	char	*get_path;

	if (count_cmd(cmd) > 1)
	{
		if (cmd[1][0] == '-' && ft_strcmp(cmd[1], "-") \
			&& ft_strcmp(cmd[1], "--"))
		{
			ft_putstr_fd(MES_PWD_OP, STDERR_FILENO);
			return (2);
		}
	}
	get_path = getcwd(NULL, 0);
	if (!get_path)
	{
		ft_putstr_fd(MES_CUR_PATH_ERR, STDERR_FILENO);
		return (1);
	}
	ft_putstr_fd(get_path, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(get_path);
	return (0);
}

int	mini_exit(t_shell *shell, t_cmd **tab_cmd, int place)
{
	int			i;
	long long	val;

	i = 1;
	if (tab_cmd[place]->cmd[i])
	{
		if (!str_to_ll(tab_cmd[place]->cmd[i], &val))
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			ft_put3str_fd("minishell: exit: ", tab_cmd[place]->cmd[i],
				MES_EXIT_NUM, STDERR_FILENO);
			free_before_exit(shell);
			exit(2);
		}
		if (tab_cmd[place]->cmd[i + 1])
			return (ft_put3str_fd("exit\n", MES_EXIT_TOO_MANY, NULL, 2), 1);
		if (val < 0)
			val = (val % 256 + 256) % 256;
		ft_putstr_fd("exit\n", STDERR_FILENO);
		free_before_exit(shell);
		exit((int)(val % 256));
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	free_before_exit(shell);
	exit(EXIT_SUCCESS);
}

int	mini_env(char **env, t_cmd **tab_cmd, int place)
{
	int	i;

	if (!env || !tab_cmd)
		return (1);
	if (tab_cmd[place] && count_cmd(tab_cmd[place]->cmd) != 1)
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

int	mini_unset(t_env **head, char **cmd)
{
	int	i;

	if (!head)
		return (1);
	i = 1;
	if (count_cmd(cmd) == 1)
		return (0);
	if (!ft_strcmp(cmd[1], "--"))
		i = 2;
	while (cmd[i])
	{
		if (cmd[1][0] == '-' && ft_strcmp(cmd[1], "--"))
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
