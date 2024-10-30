/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:20:23 by yfan              #+#    #+#             */
/*   Updated: 2024/10/29 18:20:24 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_str4join(char *s1, char *s2, char *s3, char *s4)
{
	char	*temp1;
	char	*temp2;
	char	*result;

	temp1 = ft_strjoin(s1, s2);
	temp2 = ft_strjoin(temp1, s3);
	free(temp1);
	result = ft_strjoin(temp2, s4);
	free(temp2);
	return (result);
}

char	*last_dir(char *s)
{
	int		i;
	char	**path;
	char	*tmp;

	if (!s)
		return (NULL);
	i = 0;
	path = ft_split(s, '/');
	if (!path)
		return (NULL);
	while (path[i])
		i++;
	tmp = ft_strdup(path[i - 1]);
	free_char_array(path);
	return (tmp);
}

char	*join_prompt(void)
{
	char	cwd[PATH_MAX];
	char	*current_path;
	char	*join_path;
	char	*last_path;

	if (!getcwd(cwd, PATH_MAX))
	{
		perror("getcwd() error");
		current_path = ft_strdup("$ ");
	}
	else
		current_path = ft_strjoin(cwd, "$ ");
	last_path = last_dir(current_path);
	free(current_path);
	join_path = ft_str4join(BLUE_B "yf&sw" COLOR_END, WHITE_B "@" \
		COLOR_END, RED_B "minishell*" COLOR_END, last_path);
	free(last_path);
	return (join_path);
}
