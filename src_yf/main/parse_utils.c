/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:56:01 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/08 12:56:04 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_tab_num(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (-1);
	while (tab[i])
		i++;
	return (i);
}

int	get_cmdtab_num(t_cmd **cmd_tab)
{
	int	i;

	i = 0;
	if (!cmd_tab)
		return (-1);
	while (cmd_tab[i])
		i++;
	return (i);
}

char	*lst_getstr(t_list *lst)
{
	if (!lst)
		return (NULL);
	return ((char *)lst->content);
}

void	do_noting(void *arg)
{
	long long	num;

	num = (long long)arg;
	return ;
}

void	clear_lsts(t_list **lst, t_list **redin, \
	t_list **redout, t_list **cmd_lst)
{
	ft_lstclear(redin, do_noting);
	ft_lstclear(redout, do_noting);
	ft_lstclear(cmd_lst, do_noting);
	ft_lstclear(lst, do_noting);
}
