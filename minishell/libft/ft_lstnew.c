/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:18:04 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/23 18:18:06 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*li;

	li = malloc(sizeof(t_list));
	if (li == NULL)
		return (NULL);
	li->content = content;
	li->next = NULL;
	return (li);
}
/*
#include <stdio.h>
int	main(void)
{
	t_list	*lista;

	lista = ft_lstnew((void *)"Hello");
       	printf("%s\n%p\n", (char *)(lista->content), lista->next);
	return (0);
}*/	
