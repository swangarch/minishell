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

#include "../includes/minishell.h"

void on_lst_next_token_exist(t_list **curr, t_list **redin, t_list **redout, t_list **cmd_lst)
{
	if (is_red(lst_getstr(*curr)) == REDIN || is_red(lst_getstr(*curr)) == HEREDOC)
	{
		ft_lstadd_back(redin, ft_lstnew(lst_getstr(*curr)));
		(*curr) = (*curr)->next;
		ft_lstadd_back(redin, ft_lstnew(lst_getstr(*curr)));
	}
	else if (is_red(lst_getstr(*curr)) == REDOUT || is_red(lst_getstr(*curr)) == APPEND)
	{
		ft_lstadd_back(redout, ft_lstnew(lst_getstr(*curr)));
		*curr = (*curr)->next;
		ft_lstadd_back(redout, ft_lstnew(lst_getstr(*curr)));
	}
	else
		ft_lstadd_back(cmd_lst, ft_lstnew(lst_getstr(*curr)));
}

// t_cmd *create_cmd(t_list *lst)  ///ok
// {
// 	t_list	*cmd_lst;
// 	t_list	*redin;
// 	t_list	*redout;
// 	t_list	*curr;
// 	t_cmd	*cmd;
	
// 	redin = NULL;
// 	redout = NULL;
// 	cmd_lst = NULL;
// 	curr = lst;
// 	while (curr)
// 	{
// 		if (curr->next)
// 			on_lst_next_token_exist(&curr, &redin, &redout, &cmd_lst);
// 		else if (is_red(lst_getstr(curr)) == REDIN || is_red(lst_getstr(curr)) == HEREDOC)
// 			ft_lstadd_back(&redin, ft_lstnew(lst_getstr(curr)));
// 		else if (is_red(lst_getstr(curr)) == REDOUT || is_red(lst_getstr(curr)) == APPEND)
// 			ft_lstadd_back(&redout, ft_lstnew(lst_getstr(curr)));
// 		else
// 			ft_lstadd_back(&cmd_lst, ft_lstnew(lst_getstr(curr)));
// 		curr = curr->next;
// 	}
// 	cmd = cmd_from_lsts(cmd_lst, redin, redout);
// 	clear_lsts(&lst, &redin, &redout, &cmd_lst);
// 	return (cmd);
// }

t_cmd *create_cmd(t_list *lst, t_list *cmd_lst, t_list *redin, t_list *redout)  ///ok
{
	// t_list	*cmd_lst;
	// t_list	*redin;
	// t_list	*redout;
	t_list	*curr;
	t_cmd	*cmd;
	
	// redin = NULL;
	// redout = NULL;
	// cmd_lst = NULL;
	curr = lst;
	while (curr)
	{
		if (curr->next)
			on_lst_next_token_exist(&curr, &redin, &redout, &cmd_lst);
		else if (is_red(lst_getstr(curr)) == REDIN || is_red(lst_getstr(curr)) == HEREDOC)
			ft_lstadd_back(&redin, ft_lstnew(lst_getstr(curr)));
		else if (is_red(lst_getstr(curr)) == REDOUT || is_red(lst_getstr(curr)) == APPEND)
			ft_lstadd_back(&redout, ft_lstnew(lst_getstr(curr)));
		else
			ft_lstadd_back(&cmd_lst, ft_lstnew(lst_getstr(curr)));
		curr = curr->next;
	}
	cmd = cmd_from_lsts(cmd_lst, redin, redout);
	clear_lsts(&lst, &redin, &redout, &cmd_lst);
	return (cmd);
}

t_cmd	**create_cmd_tab(char **tab)
{
	t_cmd	**tab_cmd;
	t_list	*lst_command;
	int	num;
	int	i;

	if (!tab)
		return (NULL);
	num = get_tab_num(tab);
	tab_cmd = malloc(sizeof(t_cmd**) * (num + 1));
	if (!tab_cmd)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		lst_command = tokenize_line(tab[i]);
		tab_cmd[i] = create_cmd(lst_command, 0, 0, 0);
		i++;
	}
	tab_cmd[i] = NULL;
	return (tab_cmd);
}
