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

#include "../../includes/minishell.h"

/**
 * @brief Determines the target directory for the "cd" command
 *
 * @param head Pointer to the environment variable linked list
 * @param cmd Array of command-line arguments
 * @param home_path The home directory path
 * @return Returns the target directory or NULL on error
 */
static char	*cd_set_dir(t_env **head, char **cmd, char *home_path)
{
	char	*dir;

	if (count_cmd(cmd) == 1 || (count_cmd(cmd) == 2 && !strcmp(cmd[1], "--")))
	{
		dir = mini_get_env("HOME", *head);
		if (!dir || !dir[0])
			return (ft_putstr_fd(MES_CD_HOME, STDERR_FILENO), free(dir), NULL);
	}
	else if (!strcmp(cmd[1], "-"))
	{
		dir = mini_get_env("OLDPWD", *head);
		if (!dir || !dir[0])
		{
			ft_putstr_fd(MES_CD_OLD, STDERR_FILENO);
			return (free(dir), NULL);
		}
	}
	else if (!cmd[1][0] && home_path)
		dir = ft_strdup(home_path);
	else
		dir = ft_strdup(cmd[1]);
	return (dir);
}

/**
 * @brief Changes the current working directory
 *
 * @param dir The target directory path
 * @return Returns 0 on success, or 1 on failure
 */
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

/**
 * @brief Changes the current directory and updates PWD and OLDPWD
 *
 * This function changes the working directory based on the command arguments.
 * It verifies the number of arguments, sets the target directory, and handles
 * errors during the directory change. It updates the PWD and OLDPWD environment
 * variables accordingly. If the argument is "-", it also prints the previous
 * directory. Returns 0 on success or 1 on failure.
 *
 * @param head Pointer to the environment variable linked list
 * @param cmd Array of command-line arguments
 * @param home_path The home directory path
 * @return Returns 0 on success, or 1 on failure
 */
int	mini_cd(t_env **head, char **cmd, char *home_path)
{
	char	*dir;
	char	*old_pwd;
	char	*new_pwd;

	if (!head)
		return (1);
	if (count_cmd(cmd) > 2)
		return (ft_putstr_fd(MES_CD_TOO_MANY, 2), 1);
	dir = cd_set_dir(head, cmd, home_path);
	if (!dir)
		return (1);
	if (cd_change_dir(dir))
		return (free(dir), 1);
	if (count_cmd(cmd) == 2 && !ft_strcmp(cmd[1], "-"))
	{
		ft_putstr_fd(dir, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (perror(MES_RETRIVE_DIR), free(dir), 1);
	old_pwd = mini_get_env("PWD", *head);
	set_pwd(head, "PWD", new_pwd);
	set_pwd(head, "OLDPWD", old_pwd);
	return (free(old_pwd), free(dir), free(new_pwd), 0);
}
