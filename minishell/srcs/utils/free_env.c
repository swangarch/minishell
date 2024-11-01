/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:00:16 by yfan              #+#    #+#             */
/*   Updated: 2024/10/28 19:00:17 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_env *head)
{
	t_env	*next;

	while (head)
	{
		next = head->next;
		free(head->var_name);
		free(head->content);
		free(head);
		head = next;
	}
}

void	free_env_path(char **env, char *get_path)
{
	free(get_path);
	free(env[0]);
	free(env[1]);
	free(env[2]);
	free(env[3]);
	free(env[4]);
	free(env);
}

void	free_close(t_shell *shell, int *p_fd, int num)
{
	close_multi_fd(num, p_fd);
	free_save_line(shell, p_fd, NULL);
}
