/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:43:05 by yfan              #+#    #+#             */
/*   Updated: 2024/10/28 17:43:08 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	export_print(t_env *current)
{
	size_t	len;

	while (current)
	{
		len = ft_strlen(current->var_name);
		if (ft_strcmp(current->var_name, "_="))
		{
			if (current->var_name[len - 1] != '=')
				printf(EXPORT_PRE "%s\n", current->var_name);
			else
				printf(EXPORT_PRE "%s\"%s\"\n", current->var_name, \
					current->content);
		}
		current = current->next;
	}
}

static int	export_set_var(t_env **head, char **cmd, int i, int *inval)
{
	char	**arg;

	if (!inval || !head || !cmd)
		return (1);
	while (cmd[i])
	{
		if (cmd[1][0] == '-' && ft_strcmp(cmd[1], "-") \
			&& ft_strcmp(cmd[1], "--"))
			return (ft_putstr_fd(MES_EXPORT_OP, STDERR_FILENO), 2);
		arg = split_by_equal(cmd[i]);
		if (!arg)
			return (1);
		if (!is_valid_name_equal(arg[0]))
		{
			*inval = TRUE;
			ft_put3str_fd(MES_EXP_PRE, cmd[i], MES_EXP_POST, STDERR_FILENO);
			++i;
			continue ;
		}
		set_var(head, arg, cmd[i]);
		free_char_array(arg);
		++i;
	}
	return (0);
}

int	mini_export(t_env **head, char **cmd)
{
	t_env	*current;
	int		val;
	int		i;
	int		invalid_arg;

	if (!head)
		return (1);
	current = *head;
	invalid_arg = FALSE;
	if ((count_cmd(cmd) == 1) || (count_cmd(cmd) == 2 \
		&& !ft_strcmp(cmd[1], "--")))
	{
		export_print(current);
		return (0);
	}
	i = 1;
	if (!ft_strcmp(cmd[1], "--"))
		i = 2;
	val = export_set_var(head, cmd, i, &invalid_arg);
	if (val)
		return (val);
	if (invalid_arg)
		return (1);
	return (0);
}
