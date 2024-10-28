/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_from_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:15:03 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/24 15:15:08 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**lst_to_chatab(t_list *lst)//safe
{
	int	i; 
	t_list *curr;
	char **chatab;

	i = 0;
	curr = lst;
	chatab = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!chatab)
		return (NULL);
	while (curr)
	{
		chatab[i] = (char *)(curr->content);
		curr = curr->next;
		i++;
	}
	chatab[i] = NULL;
	return (chatab);
}

static void init_cmd_struct(t_cmd *command)
{
	command->cmd = NULL;
	command->redin = NULL;
	command->redout = NULL;
	command->has_in = FALSE;
	command->has_out = FALSE;
}

static int	assign_cmd_tabs(t_cmd *command, t_list *cmd_lst, t_list *redin, t_list *redout)
{
	command->cmd = lst_to_chatab(cmd_lst);
	if (!command->cmd)
		return (0);
	command->redin = lst_to_chatab(redin);
	if (!command->redin)
	{
		free_char_array(command->cmd);
		return (0);
	}
	command->redout = lst_to_chatab(redout);
	if (!command->redout)   //if NULL means malloc fail, should avoid to access the member, in next function
	{
		free_char_array(command->cmd);
		free_char_array(command->redin);
		return (0);
	}
	return (1);
}

static t_cmd *on_no_cmd(t_cmd *command)
{
	free_char_array(command->cmd);
	command->cmd = malloc(sizeof(char *) * 2);
    if (!command->cmd)
	{
		free_char_array(command->redin);
		free_char_array(command->redout);
		free(command);
        return (NULL);
	}
	command->cmd[0] = ft_strdup("");
	if (!command->cmd[0])
	{
		free_char_array(command->redin);
		free_char_array(command->redout);
		free_char_array(command->cmd);
		free(command);
        return (NULL);
	}
	command->cmd[1] = NULL;
	return (command);
}

t_cmd *cmd_from_lsts(t_list *cmd_lst, t_list *redin, t_list *redout)  //ok
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);
	init_cmd_struct(command);
	if (!assign_cmd_tabs(command, cmd_lst, redin, redout))
	{
		free(command);
		return (NULL);
	}
	if (command->redin[0])
		command->has_in = TRUE;
	if (command->redout[0])
		command->has_out = TRUE;
	if ((command->has_in || command->has_out) && !(command->cmd[0]))   //0 command but has redirection, and previous malloc(tab) didn't fail, should free previous command and create a new one to put **tab and let tab[0] == void str 
		return (on_no_cmd(command));
	return (command);
}