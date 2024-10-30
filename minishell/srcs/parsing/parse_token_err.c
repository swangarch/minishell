/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_err.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:59:22 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/08 12:59:24 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_pipe(t_list *lst)
{
	t_list	*curr;
	int		num_pipe;

	num_pipe = 0;
	curr = lst;
	while (curr)
	{
		if (!ft_strcmp(lst_getstr(curr), "|"))
			num_pipe++;
		curr = curr->next;
	}
	return (num_pipe);
}

int	red_next_err(char **tab)
{
	int	i;

	if (!tab)
		return (-1);
	i = 0;
	while (tab[i])
	{
		if (is_red(tab[i]) != TEXT)
		{
			if (!tab[i + 1] || is_red(tab[i + 1]) != TEXT)
			{
				ft_err(ERR_PREF "syntax error near unexpected token `");
				if (tab[i + 1])
					ft_putstr_fd(tab[i + 1], 2);
				else
					ft_putstr_fd("|", 2);
				ft_err("'\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	parse_error(t_cmd **cmds)
{
	int	i;

	i = 0;
	if (!cmds)
		return (-1);
	while (cmds[i])
	{
		if (!(cmds[i]->has_in) && !(cmds[i]->has_out) && !(cmds[i]->cmd[0]))
		{
			ft_err(ERR_PREF "syntax error near unexpected token `|'\n");
			return (1);
		}
		if (red_next_err(cmds[i]->redin) || red_next_err(cmds[i]->redout))
		{
			return (1);
		}
		i++;
	}
	return (0);
}
