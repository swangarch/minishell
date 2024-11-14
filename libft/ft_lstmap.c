/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:12:23 by shuwang           #+#    #+#             */
/*   Updated: 2024/06/03 14:54:58 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_list(t_list *lst)
{
	t_list	*curr;
	int		count;

	curr = lst;
	count = 0;
	while (curr != NULL)
	{
		curr = curr->next;
		count++;
	}
	return (count);
}

static	t_list	*create_list(int count)
{
	t_list	*node;

	if (count == 0)
		return (NULL);
	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->next = create_list(count - 1);
	if (node->next == NULL && count > 1)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*curr;
	t_list	*newlst;
	t_list	*newcurr;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	curr = lst;
	newlst = create_list(count_list(lst));
	if (newlst == NULL)
		return (NULL);
	newcurr = newlst;
	while (curr != NULL)
	{
		newcurr->content = f(curr->content);
		newcurr = newcurr->next;
		curr = curr->next;
	}
	return (newlst);
}
