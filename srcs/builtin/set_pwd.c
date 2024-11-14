/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:45:33 by yfan              #+#    #+#             */
/*   Updated: 2024/10/28 18:45:42 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Initializes the environment list with the current directory
 *
 * This function checks if the environment list is empty. If so, it creates
 * a new environment node with the given directory path. It handles memory
 * allocation and cleanup appropriately.
 *
 * @param lst_env Pointer to the environment variable linked list
 * @param full The full path of the current directory
 * @return Returns 0 on success, or 1 on failure
 */
static int	set_pwd_begin(t_env **lst_env, char *full)
{
	t_env	*current;
	t_env	*new;

	current = *lst_env;
	if (!current)
	{
		new = init_env_node(full);
		if (!new)
		{
			free(full);
			return (1);
		}
		current = new;
		free(full);
		return (0);
	}
	return (0);
}

/**
 * @brief Adds a new environment node if the current node is null
 *
 * This function checks if the current environment node is null. If it is,
 * it initializes a new environment node with the provided path and adds 
 * it to the end of the environment list. It handles memory management 
 * appropriately.
 *
 * @param lst_env Pointer to the environment variable linked list
 * @param current Pointer to the current environment node
 * @param full The full path of the current directory
 */
static void	set_pwd_end(t_env **lst_env, t_env *current, char *full)
{
	t_env	*new;

	if (!current)
	{
		new = init_env_node(full);
		if (!new)
		{
			free(full);
			return ;
		}
		add_back_env_node(lst_env, new);
		free(full);
	}
}

/**
 * @brief Sets or updates an environment variable with a new value
 *
 * This function sets or updates the value of an environment variable. It 
 * constructs the variable name and its content, and if the variable 
 * already exists, its content is updated. If the variable does not 
 * exist, a new environment node is created and added to the list.
 *
 * @param lst_env Pointer to the environment variable linked list
 * @param name The name of the environment variable to set
 * @param content The value to assign to the environment variable
 */
void	set_pwd(t_env **lst_env, char *name, char *content)
{
	t_env	*current;
	char	*tmp_old;
	char	*tmp_new;

	current = *lst_env;
	tmp_old = ft_strjoin(name, "=");
	tmp_new = ft_strjoin(tmp_old, content);
	free(tmp_old);
	if (set_pwd_begin(lst_env, tmp_new))
		return ;
	while (current)
	{
		if (!ft_strncmp(current->var_name, name, ft_strlen(name)) \
			&& (current->var_name[ft_strlen(name)] == '=' \
			|| current->var_name[ft_strlen(name)] == '\0'))
		{
			free(current->content);
			current->content = ft_strdup(content);
			free(tmp_new);
			return ;
		}
		current = current->next;
	}
	set_pwd_end(lst_env, current, tmp_new);
}

void	unset_var_begin(t_env **lst_env, const char *name)
{
	t_env	*current;

	current = *lst_env;
	while (!ft_strncmp(current->var_name, name, ft_strlen(name)) \
		&& (current->var_name[ft_strlen(name)] == '=' \
		|| current->var_name[ft_strlen(name)] == '\0'))
	{
		free_2_char(current->content, current->var_name);
		*lst_env = current->next;
		free(current);
		current = *lst_env;
	}
}
