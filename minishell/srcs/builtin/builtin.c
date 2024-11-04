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

/**
 * @brief Executes the specified built-in command
 *
 * This function determines the type of built-in command to execute based on
 * the provided `type` parameter. It updates the shell's status according to
 * the result of executing the corresponding built-in command function (e.g., 
 * `mini_echo`, `mini_cd`, etc.). The function handles various built-in commands
 * such as echo, cd, pwd, export, unset, env, and exit. The execution result
 * is reflected in the shell's status, which can be used for error handling or
 * reporting.
 *
 * @param type An integer representing the type of built-in command to execute
 * @param shell Pointer to the shell structure containing shell data and commands
 * @param p_fd Pointer to an integer array for file descriptors (if needed)
 * @param i Index of the command in the tab_cmd array to be executed
 * @return Returns the status of the executed built-in command
 */
int	mini_builtin(int type, t_shell *shell, int *p_fd, int i)
{
	if (type == MINI_ECHO)
		shell->status = mini_echo(shell->tab_cmd[i]->cmd);
	else if (type == MINI_CD)
		shell->status = mini_cd(&shell->env_head, shell->tab_cmd[i]->cmd, \
			shell->home_path);
	else if (type == MINI_PWD)
		shell->status = mini_pwd(shell->tab_cmd[i]->cmd, shell->env_head);
	else if (type == MINI_EXPORT)
		shell->status = mini_export(&shell->env_head, shell->tab_cmd[i]->cmd);
	else if (type == MINI_UNSET)
		shell->status = mini_unset(&shell->env_head, shell->tab_cmd[i]->cmd);
	else if (type == MINI_ENV)
		shell->status = mini_env(shell->env, shell->tab_cmd, i);
	else if (type == MINI_EXIT)
		shell->status = mini_exit(shell, shell->tab_cmd, i, p_fd);
	return (shell->status);
}

/**
 * @brief Prints the current working directory
 *
 * This function retrieves and displays the current working directory.
 * It first checks if more than one argument is passed; if so, it verifies
 * that the second argument is not an invalid option (e.g., not "-" or "--").
 * If an invalid option is detected, an error message is printed to
 * standard error. The function then attempts to get the current directory
 * using `getcwd`. If `getcwd` fails, it falls back to retrieving the 
 * PWD environment variable. Finally, the current directory is printed to
 * standard output, followed by a newline.
 *
 * @param cmd Array of command-line arguments, with the first element
 *            being the command and subsequent elements being options
 * @param head Pointer to the environment variable linked list to access
 *             environment variables
 * @return Returns 0 on success, 2 if an invalid option is passed
 */
int	mini_pwd(char **cmd, t_env *head)
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
		get_path = mini_get_env("PWD", head);
	}
	ft_putstr_fd(get_path, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(get_path);
	return (0);
}

/**
 * @brief Exits the minishell with an optional exit status
 *
 * This function handles the exit command for the minishell. It checks
 * if an argument is provided; if so, it attempts to convert it to a
 * long long integer using `str_to_ll`. If the conversion fails, it prints
 * an error message and exits with status code 2. If too many arguments
 * are provided, it also prints a corresponding error message. If the 
 * value is negative, it adjusts it to fit within the 0-255 range.
 * Finally, it frees any resources and exits the shell with the specified
 * exit status or with the default success status if no arguments are given.
 *
 * @param shell Pointer to the shell structure containing shell data
 * @param tab_cmd Array of command-line arguments, with the first element
 *                 being the command and subsequent elements being options
 * @param place Index of the command in the tab_cmd array to be executed
 * @param p_fd Pointer to an integer array for file descriptors (if needed)
 * @return This function does not return; it exits the program
 */
int	mini_exit(t_shell *shell, t_cmd **tab_cmd, int place, int *p_fd)
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
			free_save_line(shell, p_fd, NULL);
			exit(2);
		}
		if (tab_cmd[place]->cmd[i + 1])
			return (ft_put3str_fd("exit\n", MES_EXIT_TOO_MANY, NULL, 2), 1);
		if (val < 0)
			val = (val % 256 + 256) % 256;
		ft_putstr_fd("exit\n", STDERR_FILENO);
		free_save_line(shell, p_fd, NULL);
		exit((int)(val % 256));
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	free_save_line(shell, p_fd, NULL);
	exit(EXIT_SUCCESS);
}

/**
 * @brief Displays the current environment variables
 *
 * This function prints all the environment variables to standard output.
 * It first checks if the environment array and command array are valid.
 * If the command associated with the given index has more than one argument,
 * it prints an error message indicating invalid usage. If the checks pass,
 * it iterates through the environment variables and prints each one on a
 * new line. 
 *
 * @param env Array of environment variables
 * @param tab_cmd Array of command-line arguments, with the first element
 *                 being the command and subsequent elements being options
 * @param place Index of the command in the tab_cmd array to be executed
 * @return Returns 1 if the environment or command array is invalid, 
 *         2 if an error occurs due to invalid command usage, 
 *         and 0 on success
 */
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

/**
 * @brief Unsets (removes) environment variables
 *
 * @param head Pointer to the head of the environment variable linked list
 * @param cmd Array of command-line arguments, with the first element
 *            being the command and subsequent elements being the names of
 *            environment variables to unset
 * @return Returns 1 if the head is invalid, 2 for invalid option usage, 
 *         and 0 on success
 */
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
