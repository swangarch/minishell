/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:32:04 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/28 18:49:09 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char    s[] = {0,1,2,3,4,5};
	printf("%s : %s\n", (char *)memchr(s, 0, 1), (char *)ft_memchr(s, 0, 1));
	printf("%s : %s\n", (char *)memchr(s, 2, 3), (char *)ft_memchr(s, 2, 3));
	printf("%s : %s\n", (char *)memchr(s, 2 + 256, 3), \
	(char *)ft_memchr(s, 2 + 256, 3));
	return (0);
}*/
