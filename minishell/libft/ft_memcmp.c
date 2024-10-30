/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:03:53 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/28 16:53:06 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	size_t			diff;
	unsigned char	*s1u;
	unsigned char	*s2u;

	i = 0;
	diff = 0;
	s1u = (unsigned char *)s1;
	s2u = (unsigned char *)s2;
	while (i < n)
	{
		if (s1u[i] == s2u[i])
			i++;
		else
		{
			diff = s1u[i] - s2u[i];
			break ;
		}
	}
	return (diff);
}
/*
#include <stdio.h>
int	main(void)
{
	char	sa[] = {1, 5, 4, 8};
	char	sb[] = {1, 8, 6, 9};

	printf("%d\n", ft_memcmp((const void *)sa, (const void *)sb, 2));
	return (0);
}*/	
