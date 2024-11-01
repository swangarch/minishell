/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_buildin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:04:33 by yfan              #+#    #+#             */
/*   Updated: 2024/10/29 15:04:35 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_build_in(const char *s)
{
	if (!ft_strcmp(s, "echo"))
		return (MINI_ECHO);
	if (!ft_strcmp(s, "cd"))
		return (MINI_CD);
	if (!ft_strcmp(s, "pwd"))
		return (MINI_PWD);
	if (!ft_strcmp(s, "export"))
		return (MINI_EXPORT);
	if (!ft_strcmp(s, "unset"))
		return (MINI_UNSET);
	if (!ft_strcmp(s, "env"))
		return (MINI_ENV);
	if (!ft_strcmp(s, "exit"))
		return (MINI_EXIT);
	return (NOBULTIN);
}

int	count_cmd(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		++i;
	return (i);
}

int	is_valid_name(const char *var)
{
	if (!var || *var == '\0' || (!ft_isalpha(*var) && *var != '_'))
		return (FALSE);
	++var;
	while (*var)
	{
		if (!ft_isalnum(*var) && *var != '_')
		{
			return (FALSE);
		}
		++var;
	}
	return (TRUE);
}

int	is_valid_name_equal(const char *var)
{
	if (!var || *var == '\0' || (!ft_isalpha(*var) && *var != '_'))
		return (FALSE);
	++var;
	while (*var)
	{
		if (!ft_isalnum(*var) && *var != '_')
		{
			if (*var == '=' && *(var + 1) == '\0')
				return (TRUE);
			return (FALSE);
		}
		++var;
	}
	return (TRUE);
}
