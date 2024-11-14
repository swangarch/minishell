/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_creat_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:27:39 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/23 18:27:40 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	on_lst_next_token_exist(t_list **curr, t_list **red, t_list **cmd_lst)
{
	if (is_red(lst_getstr(*curr)) == 1 || is_red(lst_getstr(*curr)) == 2)
	{
		ft_lstadd_back(red, ft_lstnew(lst_getstr(*curr)));
		(*curr) = (*curr)->next;
		ft_lstadd_back(red, ft_lstnew(lst_getstr(*curr)));
	}
	else if (is_red(lst_getstr(*curr)) == 3 || is_red(lst_getstr(*curr)) == 4)
	{
		ft_lstadd_back(red, ft_lstnew(lst_getstr(*curr)));
		*curr = (*curr)->next;
		ft_lstadd_back(red, ft_lstnew(lst_getstr(*curr)));
	}
	else
		ft_lstadd_back(cmd_lst, ft_lstnew(lst_getstr(*curr)));
}

t_cmd	*create_cmd(t_list *lst, t_list *cmd_lst, t_list *red)
{
	t_list	*curr;
	t_cmd	*cmd;

	curr = lst;
	while (curr)
	{
		if (curr->next)
			on_lst_next_token_exist(&curr, &red, &cmd_lst);
		else if (is_red(lst_getstr(curr)) == 1 || is_red(lst_getstr(curr)) == 2)
			ft_lstadd_back(&red, ft_lstnew(ft_strdup(lst_getstr(curr))));
		else if (is_red(lst_getstr(curr)) == 3 || is_red(lst_getstr(curr)) == 4)
			ft_lstadd_back(&red, ft_lstnew(ft_strdup(lst_getstr(curr))));
		else
			ft_lstadd_back(&cmd_lst, ft_lstnew(lst_getstr(curr)));
		curr = curr->next;
	}
	cmd = cmd_from_lsts(cmd_lst, red);
	clear_lsts(&lst, &red, &cmd_lst);
	return (cmd);
}

int	has_in(char **red)
{
	int	i;

	i = 0;
	while (red[i])
	{
		if (is_red(red[i]) == REDIN || is_red(red[i]) == HEREDOC)
			return (1);
		i++;
	}
	return (0);
}

int	has_out(char **red)
{
	int	i;

	i = 0;
	while (red[i])
	{
		if (is_red(red[i]) == REDOUT || is_red(red[i]) == APPEND)
			return (1);
		i++;
	}
	return (0);
}

t_cmd	**create_cmd_tab(char **tab)
{
	t_cmd	**tab_cmd;
	t_list	*lst_command;
	int		num;
	int		i;

	if (!tab)
		return (NULL);
	num = get_tab_num(tab);
	tab_cmd = malloc(sizeof(t_cmd *) * (num + 1));
	if (!tab_cmd)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		lst_command = tokenize_line(tab[i]);
		tab_cmd[i] = create_cmd(lst_command, 0, 0);
		i++;
	}
	tab_cmd[i] = NULL;
	return (tab_cmd);
}
