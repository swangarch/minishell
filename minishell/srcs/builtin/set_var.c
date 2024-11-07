/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:28:28 by yfan              #+#    #+#             */
/*   Updated: 2024/10/28 18:28:31 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Unsets an environment variable by its name
 *
 * This function removes all occurrences of a specified environment 
 * variable from the linked list. It frees the associated memory for 
 * both the variable name and its content. If the variable is found 
 * at the head of the list, it updates the head pointer accordingly.
 *
 * @param lst_env Pointer to the environment variable linked list
 * @param name The name of the environment variable to unset
 */
void	unset_var(t_env **lst_env, const char *name)
{
	t_env	*prev;
	t_env	*current;

	current = *lst_env;
	unset_var_begin(lst_env, name);
	prev = current;
	current = current->next;
	while (current)
	{
		if (!ft_strncmp(current->var_name, name, ft_strlen(name)) \
			&& (current->var_name[ft_strlen(name)] == '=' \
			|| current->var_name[ft_strlen(name)] == '\0'))
		{
			free_2_char(current->content, current->var_name);
			prev->next = current->next;
			free(current);
			current = prev;
		}
		prev = current;
		current = current->next;
	}
}

/**
 * @brief Initializes a new environment variable node if the list is empty
 *
 * This function checks if the linked list of environment variables is empty. 
 * If it is, it creates a new node using the provided command string. 
 * Returns 1 if memory allocation fails.
 *
 * @param lst_env Pointer to the environment variable linked list
 * @param cmd Command string for initializing the new variable
 * @return 0 if successful, 1 if memory allocation fails
 */
static int	set_var_begin(t_env **lst_env, char *cmd)
{
	t_env	*current;
	t_env	*new;

	current = *lst_env;
	if (!current)
	{
		new = init_env_node(cmd);
		if (!new)
		{
			return (1);
		}
		current = new;
	}
	return (0);
}

/**
 * @brief Adds a new environment variable node to the end of the list
 *
 * @param lst_env Pointer to the environment variable linked list
 * @param current Pointer to the current environment variable node
 * @param cmd Command string for initializing the new variable
 */
static void	set_var_end(t_env **lst_env, t_env *current, char *cmd)
{
	t_env	*new;

	if (!current)
	{
		new = init_env_node(cmd);
		if (!new)
		{
			return ;
		}
		add_back_env_node(lst_env, new);
	}
}

/**
 * @brief Checks if the current environment variable matches the given name
 *
 * @param current Pointer to the current environment variable node
 * @param tmp Temporary variable name to compare with
 * @param name Array containing the new variable name and its value
 * @return Returns 0 if the variable was updated, 1 if it was not found
 */
static int	set_var_check_equal(t_env *current, char *tmp, char **name)
{
	if (!ft_strncmp(current->var_name, tmp, ft_strlen(tmp)) \
		&& (current->var_name[ft_strlen(tmp)] == '=' \
		|| current->var_name[ft_strlen(tmp)] == '\0'))
	{
		if (ft_strlen(tmp) != ft_strlen(name[0]))
		{
			free_2_char(current->content, current->var_name);
			current->content = ft_strdup(name[1]);
			current->var_name = ft_strdup(name[0]);
			return (0);
		}
		else
			return (0);
	}
	return (1);
}

/**
 * @brief Sets or updates an environment variable in the linked list
 *
 * This function checks if the environment variable already exists; if it does,
 * it updates its value and name. If not, it adds a new variable to the list.
 *
 * @param lst_env Double pointer to the linked list of environment variables
 * @param name Array containing the variable name and value
 * @param cmd The original command string used to set the variable
 */
void	set_var(t_env **lst_env, char **name, char *cmd)
{
	t_env	*current;
	char	*tmp;

	if (set_var_begin(lst_env, cmd))
		return ;
	current = *lst_env;
	tmp = ft_strtrim(name[0], "=");
	if (!tmp)
		return ;
	while (current)
	{
		if (!set_var_check_equal(current, tmp, name))
			return (free(tmp), (void)0);
		current = current->next;
	}
	free(tmp);
	set_var_end(lst_env, current, cmd);
}
