/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:51:24 by yfan              #+#    #+#             */
/*   Updated: 2024/10/28 18:51:28 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_path_access(char *cmd, t_shell *shell, int *p_fd)
{
	char	*tmp;

	if (access(cmd, F_OK | X_OK) == 0)
		return (0);
	tmp = mini_get_env("PATH", shell->env_head);
	if (!tmp || !tmp[0])
	{
		ft_put3str_fd(SHELL, cmd, MES_CD_ENOENT, STDERR_FILENO);
		free_save_line(shell, p_fd, tmp);
		exit(127);
	}
	free(tmp);
	if (ft_strchr(cmd, '/') && access(cmd, F_OK))
	{
		ft_put3str_fd(SHELL, cmd, MES_CD_ENOENT, STDERR_FILENO);
		free_save_line(shell, p_fd, NULL);
		exit(127);
	}
	if (ft_strchr(cmd, '/') && access(cmd, X_OK))
	{
		ft_put3str_fd(SHELL, cmd, MES_CD_EACCES, STDERR_FILENO);
		free_save_line(shell, p_fd, NULL);
		exit(126);
	}
	return (1);
}

static char	*get_full_path(char *cmd, char *path)
{
	char	*part_path;
	char	*full_path;

	part_path = ft_strjoin(path, "/");
	if (!part_path)
		return (NULL);
	full_path = ft_strjoin(part_path, cmd);
	free(part_path);
	return (full_path);
}

static int	validate_access(char *cmd, char *full_path, char **all_path)
{
	if (access(full_path, F_OK) == 0)
	{
		if (access(full_path, X_OK))
		{
			ft_put3str_fd(SHELL, cmd, MES_CD_EACCES, STDERR_FILENO);
			free_char_array(all_path);
			free(full_path);
			exit(126);
		}
		free_char_array(all_path);
		return (TRUE);
	}
	return (FALSE);
}

char	*get_path(char *cmd, t_shell *shell, int *p_fd)
{
	int		i;
	char	*full_path;
	char	**all_path;

	i = -1;
	if (!check_path_access(cmd, shell, p_fd))
		return (ft_strdup(cmd));
	all_path = env_split(shell->env);
	if (!all_path)
		return (NULL);
	while (all_path[++i])
	{
		full_path = get_full_path(cmd, all_path[i]);
		if (!full_path)
			return (free_char_array(all_path), NULL);
		if (validate_access(cmd, full_path, all_path))
			return (full_path);
		free(full_path);
	}
	return (free_char_array(all_path), NULL);
}

char	**env_split(char **env)
{
	int		i;
	char	**all_path;

	i = 0;
	while (env && env[i] && ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	if (!i || !env[i])
		return (NULL);
	all_path = ft_split(env[i] + 5, ':');
	if (!all_path)
		return (NULL);
	return (all_path);
}
