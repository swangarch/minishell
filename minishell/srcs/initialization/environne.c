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
	size_t	size;
	size_t	i;

	i = 0;
	size = get_env_list_size(env);
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (NULL);
	result[size] = NULL;
	while (env != NULL && i < size)
	{
		if (env->var_name[ft_strlen(env->var_name) - 1] != '=')
		{
			env = env->next;
			continue ;
		}
		result[i] = get_full_env(env);
		if (!result[i])
			result[i] = strdup("");
		env = env->next;
		i++;
	}
	return (result);
}

size_t	get_env_list_size(t_env *head)
{
	t_env	*curr;
	size_t	i;
	size_t	len;

	i = 0;
	curr = head;
	while (curr != NULL)
	{
		len = ft_strlen(curr->var_name);
		if (curr->var_name[len - 1] == '=')
			++i;
		curr = curr->next;
	}
	return (i);
}

char	*get_full_env(t_env *env)
{
	char	*result;

	if (env->content != NULL)
	{
		result = ft_strjoin(env->var_name, env->content);
	}
	else
		return (env->var_name);
	return (result);
}

char	*mini_get_env(const char *name, t_env *lst_env)
{
	while (lst_env)
	{
		if (!ft_strncmp(lst_env->var_name, name, ft_strlen(name)) \
			&& (lst_env->var_name[ft_strlen(name)] == '=' \
			|| lst_env->var_name[ft_strlen(name)] == '\0'))
			return (ft_strdup(lst_env->content));
		lst_env = lst_env->next;
	}
	return (ft_strdup(""));
}
