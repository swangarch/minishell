/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:05:22 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/30 20:18:21 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*freenode;

	curr = *lst;
	if (*lst == NULL || del == NULL)
		return ;
	while (curr != NULL)
	{
		del(curr->content);
		curr->content = NULL;
		freenode = curr;
		curr = curr->next;
		free(freenode);
		freenode = NULL;
	}
	*lst = NULL;
}
