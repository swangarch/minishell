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

#include "../includes/minishell.h"

int		count_pipe(t_list *lst)
{
	t_list	*curr;
	int		num_pipe;

	num_pipe = 0;
	curr = lst;
	while (curr)
	{
		if (!ft_strcmp((char*)(curr->content), "|")) 
			num_pipe++;
		curr = curr->next;
	}
	return (num_pipe);
}

int		check_double_pipe(t_list *lst)///check if pipe is in the end
{
	t_list	*curr;
	//int		has_double_pipe;

	//if (!lst)
	//	return (NULL);
	//has_double_pipe = 0;  //protect content
	curr = lst;
	while (curr)
	{
		if (!ft_strcmp((char*)(curr->content), "|") && curr->next && !ft_strcmp((char*)(curr->next->content), "|"))
		{
			ft_err(ERR_PREF "syntax error near unexpected token `|'\n");
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int		check_red_file(t_list *lst)///check if pipe is in the end
{
	t_list	*curr_quick;
	t_list	*curr_slow;

	curr_quick = lst;
	while (curr_quick)
	{
		curr_slow = curr_quick;
		curr_quick = curr_quick->next;
		if (is_red((char*)(curr_slow->content)) > 0 && is_red((char*)(curr_quick->content)) > 0)
		{
			ft_err(ERR_PREF "syntax error near unexpected token `><'\n"); /////////////////fix
			return (1);
		}
	}
	return (0);
}

int		check_token_err(t_list *lst)
{
	int	token_err;

	token_err = 0;
	token_err = token_err + check_double_pipe(lst);
	token_err = token_err + check_red_file(lst);
	if (token_err)
		return (1);
	return (0);
}