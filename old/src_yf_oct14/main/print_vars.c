/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:52:01 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/08 12:52:13 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	print_tab(char **s)
// {
// 	int	i;

// 	i = 0;
// 	if (!s)
// 		return ;
// 	while (s[i])
// 	{
// 		ft_putstr(s[i]);
// 		write(1, "$", 1);
// 		write(1, "\n", 1);
// 		i++;
// 	}
// 	write(1, "\n", 1);
// }

void	print_tab(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putstr(s[i]);
		if (s[i + 1])
			write(1, "__", 2);
		i++;
	}
	write(1, "\n", 1);
}

void	print_lst(t_list *lst)
{
	t_list *curr;

	curr = lst;
	while (curr)
	{
		if (curr->content == NULL)
			return ;
		ft_putstr((char *)(curr->content));
		if (curr->next)
			write(1, "___", 3);
		curr = curr->next;
	}
	write(1, "$", 1);
	write(1, "\n", 1);
}

void	print_lst_partition(t_list **partition)
{
	int	i = 0;

	if (!partition)
		return ;
	while(partition[i])
	{
		print_lst(partition[i]);
		i++;
	}
}

void	print_token_struct(t_lstcmd *cmd_lst)
{
	if (!cmd_lst)
		return ;
	ft_putstr("The command is:  ");
	print_lst(cmd_lst->full_cmd);
	ft_putstr("The redirection in is:  ");
	print_lst(cmd_lst->redin);
	ft_putstr("The redirection out is:  ");
	print_lst(cmd_lst->redout);
	write(1, "\n", 1);
}

void	print_token_str(t_strcmd *cmd_str)
{
	int	i;

	if (!cmd_str)
		return ;
	i = 0;
	ft_putstr(GREEN "RED_IN :  " COLOR_END);
	print_tab(cmd_str->redin);
	ft_putstr(GREEN "RED_OUT:  " COLOR_END);
	print_tab(cmd_str->redout);
	ft_putstr(GREEN "CMD_TAB:  \n" COLOR_END);
	while (cmd_str->tab_cmd[i])
	{
		ft_putstr("          ");
		print_tab(cmd_str->tab_cmd[i]);
		i++;
	}
	printf(GREEN "CMD_NUM:  %d\n" COLOR_END, cmd_str->num_cmd);
}
