/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:31:48 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/29 17:45:18 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char			*cha;
	size_t			i;

	i = 0;
	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (nmemb > ((size_t) - 1) / size)
		return (NULL);
	cha = malloc(nmemb * size);
	if (cha == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		cha[i] = 0;
		i++;
	}
	return (cha);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*ch;
	int	i;
	
	i = 0;
	ch = ft_calloc(5, 10);
	if (ch == NULL)
		printf("%s\n", ch);
	while (i < 50)
	{
		printf("%d\n", ch[i]);
		i++;
	}
}*/
