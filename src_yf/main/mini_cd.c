/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:22:44 by yfan              #+#    #+#             */
/*   Updated: 2024/10/28 18:22:55 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*cd_set_dir(t_env **head, char **cmd)
{
	char	*dir;

	if (count_cmd(cmd) == 1)
	{
		dir = mini_get_env("HOME", *head);
		if (!dir || !dir[0])
		{
			ft_putstr_fd(MES_CD_HOME, STDERR_FILENO);
			return (free(dir), NULL);
		}
	}
	else if (!strcmp(cmd[1], "-"))
	{
		dir = mini_get_env("OLDPWD", *head);
		if (!dir || !dir[0])
		{
			ft_putstr_fd(MES_CD_OLD, STDERR_FILENO);
			return (free(dir), NULL);
		}
		ft_putstr_fd(dir, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else
		dir = ft_strdup(cmd[1]);
	return (dir);
}

static int	cd_change_dir(char *dir)
{
	if (chdir(dir) != 0)
	{
		if (errno == ENOENT)
			ft_put3str_fd(SHELL "cd: ", dir,
				MES_CD_ENOENT, STDERR_FILENO);
		else if (errno == ENOTDIR)
			ft_put3str_fd(SHELL "cd: ", dir,
				MES_CD_ENOTDIR, STDERR_FILENO);
		else if (errno == EACCES)
			ft_put3str_fd(SHELL "cd: ", dir,
				MES_CD_EACCES, STDERR_FILENO);
		else
		{
			ft_put3str_fd(SHELL "cd: ", dir, ": ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
		}
		return (1);
	}
	return (0);
}

int	mini_cd(t_env **head, char **cmd)
{
	char	*dir;
	char	*old_pwd;
	char	*new_pwd;

	if (!head)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (ft_putstr_fd(MES_CUR_PATH_ERR, STDERR_FILENO), 1);
	if (count_cmd(cmd) > 2)
		return (ft_putstr_fd(MES_CD_TOO_MANY, 2), free(old_pwd), 1);
	dir = cd_set_dir(head, cmd);
	if (!dir)
		return (free(old_pwd), 1);
	if (!dir[0])
		return (free(old_pwd), 0);
	if (cd_change_dir(dir))
		return (free(old_pwd), free(dir), 1);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (ft_putstr_fd(MES_CUR_PATH_ERR, STDERR_FILENO),
			free(old_pwd), free(dir), 1);
	set_pwd(head, "PWD", new_pwd);
	set_pwd(head, "OLDPWD", old_pwd);
	return (free(old_pwd), free(dir), free(new_pwd), 0);
}
