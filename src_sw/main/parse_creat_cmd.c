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

void init_cmd_struct(t_cmd *command)
{
	command->cmd = NULL;
	command->redin = NULL;
	command->redout = NULL;
	command->has_in = FALSE;
	command->has_out = FALSE;
}

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

t_cmd *creat_cmd_from_lsts(t_list *cmd_lst, t_list *redin, t_list *redout)  //ok
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);
	init_cmd_struct(command);
	command->cmd = lst_to_chatab(cmd_lst);
	command->redin = lst_to_chatab(redin);
	command->redout = lst_to_chatab(redout);
	if (command->redin[0])
		command->has_in = TRUE;
	if (command->redout[0])
		command->has_out = TRUE;
	if ((command->has_in || command->has_out) && !(command->cmd[0]))
	{
		command->cmd = malloc(sizeof(char *) * 2);//protect !!!!!!!!!
        if (!command->cmd)
            return (command);////////////???????????????check impact of this operation
		command->cmd[0] = ft_strdup("");//
		command->cmd[1] = NULL;
	}
	return (command);
}

t_cmd *creat_cmd(t_list *lst)  ///ok
{
	t_list	*cmd_lst;
	t_list	*redin;
	t_list	*redout;
	t_list	*curr;
	t_cmd	*cmd;
	
	redin = NULL;
	redout = NULL;
	cmd_lst = NULL;
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
	cmd = creat_cmd_from_lsts(cmd_lst, redin, redout);
	clear_lsts(&lst, &redin, &redout, &cmd_lst);
	return (cmd);
}

t_cmd	**creat_cmd_tab(char **tab)
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
		lst_command = split_line(tab[i]);
		tab_cmd[i] = creat_cmd(lst_command);
		i++;
	}
	tab_cmd[i] = NULL;
	return (tab_cmd);
}
