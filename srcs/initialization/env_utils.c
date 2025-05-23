/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:06:27 by yfan              #+#    #+#             */
/*   Updated: 2024/10/29 15:06:28 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*init_default_env(char **env)
{
	size_t	i;
	t_env	*head;
	t_env	*new;

	i = 0;
	head = init_env_node(env[i++]);
	if (!head)
		return (NULL);
	while (env[i])
	{
		new = init_env_node(env[i]);
		if (!new)
		{
			free_env(head);
			return (NULL);
		}
		add_back_env_node(&head, new);
		++i;
	}
	return (head);
}

t_env	*init_env_node(char *str)
{
	char	**split;
	t_env	*env_node;

	env_node = (t_env *)malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);
	split = split_by_equal(str);
	if (!split)
		return (free(env_node), NULL);
	env_node->var_name = ft_strdup(split[0]);
	if (!env_node->var_name)
		return (free_char_array(split), free(env_node), NULL);
	env_node->content = get_env_content(str, split[0]);
	if (!env_node->content)
		return (free(env_node->var_name), free(env_node),
			free_char_array(split), NULL);
	env_node->next = NULL;
	free_char_array(split);
	return (env_node);
}

char	*get_env_content(char *full, char *var_name)
{
	int		i;
	int		j;
	char	*content;
	size_t	content_len;
	size_t	var_name_len;

	var_name_len = ft_strlen(var_name);
	if (var_name_len == ft_strlen(full))
		content = ft_strdup("");
	else
	{
		content_len = ft_strlen(full) - var_name_len;
		content = (char *)malloc(sizeof(char) * (content_len + 1));
		if (!content)
			return (NULL);
		i = var_name_len;
		j = -1;
		while (full[i + ++j] != '\0')
			content[j] = full[i + j];
		content[j] = '\0';
	}
	return (content);
}

void	add_back_env_node(t_env **head, t_env *new)
{
	t_env	*curr;

	if (!head)
		return ;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

void	update_env(t_shell *shell)
{
	if (shell->env != NULL)
	{
		free_char_array(shell->env);
		shell->env = NULL;
	}
	shell->env = env_list_to_char(shell->env_head);
}
