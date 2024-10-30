/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:26:18 by shuwang           #+#    #+#             */
/*   Updated: 2024/06/18 16:20:19 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear_gnl(t_clist **lst)
{
	t_clist	*curr;
	t_clist	*freenode;

	curr = *lst;
	if (*lst == NULL)
		return ;
	while (curr != NULL)
	{
		freenode = curr;
		curr = curr->next;
		free(freenode);
	}
	*lst = NULL;
}

void	ft_lstadd_back_gnl(t_clist **lst, t_clist *new)
{
	t_clist	*current;

	current = *lst;
	if (*lst != NULL && new != NULL)
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
	else if (*lst == NULL && new != NULL)
		*lst = new;
}

t_clist	*copy_tolist(t_clist **lst, const char *src, int size)
{
	int		i;
	t_clist	*li;

	i = 0;
	while (i < size)
	{
		li = malloc(sizeof(t_clist));
		if (li == NULL)
		{
			ft_lstclear_gnl(lst);
			return (NULL);
		}
		li->content = src[i];
		li->next = NULL;
		ft_lstadd_back_gnl(lst, li);
		i++;
	}
	return (*lst);
}

int	lst_find_nl(t_clist *lst)
{
	t_clist	*curr;

	curr = lst;
	while (curr)
	{
		if (curr->content == '\n')
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	lst_count_nlorend(t_clist *lst)
{
	int		count;
	t_clist	*curr;

	count = 0;
	curr = lst;
	while (curr)
	{
		if (curr->content == '\n')
		{
			count++;
			return (count);
		}
		curr = curr->next;
		count++;
	}
	return (count);
}
/*
#include <stdio.h>

int main(void)
{
    char    s[80] = "Hello world\n\n\nnice to meet you\nlet's play a game";
    t_clist  *lst = NULL;
	char	*str;

    copy_tolist(&lst, s, 80);
    str = lst_get_line(&lst);
	printf("%s", str);
	free(str);
	str = lst_get_line(&lst);
	printf("%s", str);
	free(str);
	str = lst_get_line(&lst);
	printf("%s", str);
	free(str);
	str = lst_get_line(&lst);
	printf("%s", str);
	free(str);
	str = lst_get_line(&lst);
	printf("%s", str);
	free(str);
	
    return (0);
}*/
