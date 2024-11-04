/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_buildin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:04:33 by yfan              #+#    #+#             */
/*   Updated: 2024/10/29 15:04:35 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Checks if the given string is a built-in command
 *
 * This function compares the provided string `s` against a list of known
 * built-in commands in the shell (e.g., echo, cd, pwd, export, unset, env,
 * exit). It returns a predefined constant representing the type of the
 * built-in command if a match is found. If the string does not match any
 * built-in command, it returns `NOBULTIN` to indicate that the command is
 * not built-in.
 *
 * @param s Pointer to the string representing the command to check
 * @return Returns a constant indicating the type of built-in command or
 *         `NOBULTIN` if the command is not a built-in command
 */
int	is_build_in(const char *s)
{
	if (!ft_strcmp(s, "echo"))
		return (MINI_ECHO);
	if (!ft_strcmp(s, "cd"))
		return (MINI_CD);
	if (!ft_strcmp(s, "pwd"))
		return (MINI_PWD);
	if (!ft_strcmp(s, "export"))
		return (MINI_EXPORT);
	if (!ft_strcmp(s, "unset"))
		return (MINI_UNSET);
	if (!ft_strcmp(s, "env"))
		return (MINI_ENV);
	if (!ft_strcmp(s, "exit"))
		return (MINI_EXIT);
	return (NOBULTIN);
}

/**
 * @brief Counts the number of commands in a string array
 *
 * This function counts and returns the number of non-null strings
 * in the provided array of strings (commonly used for command-line
 * arguments). If the input array is null, it returns 0. The count
 * is determined by iterating through the array until a null pointer
 * is encountered.
 *
 * @param str Pointer to an array of strings (commands)
 * @return Returns the number of commands in the array, or 0 if the array is null
 */
int	count_cmd(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		++i;
	return (i);
}

/**
 * @brief Checks if a string is a valid variable name
 *
 * This function verifies whether the provided string `var` meets the criteria
 * for a valid variable name in the shell. A valid variable name must start
 * with an alphabetic character or an underscore, and subsequent characters
 * can be alphanumeric or underscores. If the input string is null, empty, or
 * does not conform to these rules, the function returns `FALSE`. Otherwise,
 * it returns `TRUE` to indicate a valid variable name.
 *
 * @param var Pointer to the string to be checked
 * @return Returns `TRUE` if the string is a valid variable name, 
 *         `FALSE` otherwise
 */
int	is_valid_name(const char *var)
{
	if (!var || *var == '\0' || (!ft_isalpha(*var) && *var != '_'))
		return (FALSE);
	++var;
	while (*var)
	{
		if (!ft_isalnum(*var) && *var != '_')
		{
			return (FALSE);
		}
		++var;
	}
	return (TRUE);
}

/**
 * @brief Checks if a string is a valid variable name with an optional assignment
 *
 * @param var Pointer to the string to be checked
 * @return Returns `TRUE` if the string is a valid variable name or a valid
 *         assignment, `FALSE` otherwise
 */
int	is_valid_name_equal(const char *var)
{
	if (!var || *var == '\0' || (!ft_isalpha(*var) && *var != '_'))
		return (FALSE);
	++var;
	while (*var)
	{
		if (!ft_isalnum(*var) && *var != '_')
		{
			if (*var == '=' && *(var + 1) == '\0')
				return (TRUE);
			return (FALSE);
		}
		++var;
	}
	return (TRUE);
}
