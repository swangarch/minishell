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

# include "minishell.h"

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
