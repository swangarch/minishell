/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:11:29 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/21 17:31:20 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>
int	main(void)
{
	int	n;
	unsigned char     b[100];
	void	*s = b;
	size_t	i;
	int	c = 'a';
	i = 0;
	n = 10;

	s = ft_memset(s, c, n); 
	while (i < n)
	{	
		printf("%c\n", ((unsigned char*)s)[i]);
		i++;		
	}
	return (0);
}*/
