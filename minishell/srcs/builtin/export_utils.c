/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:01:20 by yfan              #+#    #+#             */
/*   Updated: 2024/11/08 12:01:36 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	list_size_all(t_env *head)
{
	t_env	*curr;
	size_t	i;

	i = 0;
	curr = head;
	while (curr != NULL)
	{
		++i;
		curr = curr->next;
	}
	return (i);
}

static int	export_strcmp(char	*s1, char	*s2)
{
	while (*s1 && *s1 == *s2 && *s1 != '=')
	{
		s1++;
		s2++;
	}
	if (*s1 == '=' && *s2 != '=')
		return (-1);
	if (*s1 != '=' && *s2 == '=')
		return (1);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static void	sort_char_array(char **name)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	while (name[i])
	{
		j = i + 1;
		while (name[j])
		{
			if (export_strcmp(name[i], name[j]) > 0)
			{
				tmp = name[i];
				name[i] = name[j];
				name[j] = tmp;
			}
			++j;
		}
		++i;
	}
}

char	**export_sort_name(t_env *head)
{
	char	**name;
	size_t	size;
	size_t	i;

	size = list_size_all(head);
	name = (char **)malloc((size + 1) * sizeof(char *));
	if (!name)
		return (NULL);
	i = 0;
	while (head)
	{
		name[i] = ft_strdup(head->var_name);
		if (!name[i])
			return (free_char_array(name), NULL);
		++i;
		head = head->next;
	}
	name[i] = NULL;
	sort_char_array(name);
	return (name);
}
