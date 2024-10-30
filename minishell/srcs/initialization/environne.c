/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environne.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:08:46 by yfan              #+#    #+#             */
/*   Updated: 2024/10/29 15:08:48 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**env_list_to_char(t_env *env)
{
	char	**result;
	int		size;
	int		i;

	i = 0;
	size = get_env_list_size(env);
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (NULL);
	result[size] = NULL;
	while (env != NULL && i < size)
	{
		result[i] = get_full_env(env);
		if (!result[i])
			result[i] = strdup("");
		env = env->next;
		i++;
	}
	return (result);
}

int	get_env_list_size(t_env *head)
{
	t_env	*curr;
	int		i;

	i = 0;
	curr = head;
	while (curr != NULL)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}

char	*get_full_env(t_env *env)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(env->var_name, "=");
	if (!tmp)
		return (NULL);
	if (env->content != NULL)
	{
		result = ft_strjoin(tmp, env->content);
		free(tmp);
	}
	else
		return (tmp);
	return (result);
}

char	*mini_get_env(const char *name, t_env *lst_env)
{
	while (lst_env)
	{
		if (!ft_strcmp(lst_env->var_name, name))
			return (ft_strdup(lst_env->content));
		lst_env = lst_env->next;
	}
	return (ft_strdup(""));
}
