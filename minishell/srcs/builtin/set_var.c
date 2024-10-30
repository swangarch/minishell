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

void	unset_var(t_env **lst_env, const char *name)
{
	t_env	*prev;
	t_env	*current;

	current = *lst_env;
	while (!ft_strcmp(current->var_name, name))
	{
		free_2_char(current->content, current->var_name);
		*lst_env = current->next;
		free(current);
		current = *lst_env;
	}
	prev = current;
	current = current->next;
	while (current)
	{
		if (!ft_strcmp(current->var_name, name))
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

void	set_var(t_env **lst_env, char **name, char *cmd)
{
	t_env	*current;

	if (set_var_begin(lst_env, cmd))
		return ;
	current = *lst_env;
	while (current)
	{
		if (!ft_strcmp(current->var_name, name[0]))
		{
			free(current->content);
			current->content = ft_strdup(name[1]);
			return ;
		}
		current = current->next;
	}
	set_var_end(lst_env, current, cmd);
}
