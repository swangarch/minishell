/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:43:05 by yfan              #+#    #+#             */
/*   Updated: 2024/10/28 17:43:08 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Prints environment variables in export format
 *
 * This function iterates through the linked list of environment
 * variables and prints each variable in the format suitable for
 * export. It excludes the variable with the name "_=". If a variable
 * has no value, it prints only the name; otherwise, it prints
 * the name and value in quotes.
 *
 * @param current Pointer to the current environment variable node
 */
static void	export_print(t_env *current)
{
	size_t	len;
	size_t	i;
	char	**name;
	char	*content;

	i = 0;
	name = export_sort_name(current);
	if (!name)
		return ;
	while (name[i])
	{
		len = ft_strlen(name[i]);
		content = mini_get_env(name[i], current);
		if (ft_strcmp(name[i], "_="))
		{
			if (name[i][len - 1] != '=')
				printf(EXPORT_PRE "%s\n", name[i]);
			else
				printf(EXPORT_PRE "%s\"%s\"\n", name[i], content);
		}
		free(content);
		++i;
	}
	free_char_array(name);
}

/**
 * @brief Sets environment variables based on command arguments
 *
 * This function processes the command arguments to set environment
 * variables. It checks for invalid options, splits arguments by the
 * '=' character, and verifies variable names. Invalid variables are
 * reported, while valid ones are added to the environment.
 *
 * @param head Pointer to the environment variable linked list
 * @param cmd Array of command-line arguments
 * @param i Current index in the command arguments
 * @param inval Pointer to an integer indicating invalid input status
 * @return Returns 0 on success, or 1 for failure, 2 for invalid options
 */
static int	export_set_var(t_env **head, char **cmd, int i, int *inval)
{
	char	**arg;

	if (!inval || !head || !cmd)
		return (1);
	while (cmd[i])
	{
		if (cmd[1][0] == '-' && ft_strcmp(cmd[1], "-") \
			&& ft_strcmp(cmd[1], "--"))
			return (ft_putstr_fd(MES_EXPORT_OP, STDERR_FILENO), 2);
		arg = split_by_equal(cmd[i]);
		if (!arg)
			return (1);
		if (!is_valid_name_equal(arg[0]))
		{
			*inval = TRUE;
			ft_put3str_fd(MES_EXP_PRE, cmd[i], MES_EXP_POST, STDERR_FILENO);
			++i;
			free_char_array(arg);
			continue ;
		}
		set_var(head, arg, cmd[i]);
		free_char_array(arg);
		++i;
	}
	return (0);
}

int	mini_export(t_env **head, char **cmd)
{
	t_env	*current;
	int		val;
	int		i;
	int		invalid_arg;

	if (!head)
		return (1);
	current = *head;
	invalid_arg = FALSE;
	if ((count_cmd(cmd) == 1) || (count_cmd(cmd) == 2 \
		&& !ft_strcmp(cmd[1], "--")))
	{
		export_print(current);
		return (0);
	}
	i = 1;
	if (!ft_strcmp(cmd[1], "--"))
		i = 2;
	val = export_set_var(head, cmd, i, &invalid_arg);
	if (val)
		return (val);
	if (invalid_arg)
		return (1);
	return (0);
}
