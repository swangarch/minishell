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

#include "../includes/minishell.h"

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
		if (!ft_strcmp(current->var_name, name))
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
