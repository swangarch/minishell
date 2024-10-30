/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:37:53 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/28 14:08:27 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
	const char	*a;
	const char	*b;
	const char	*c;
	a = ft_strchr("Hello world",'r');
	b = ft_strchr("Hello world",'\0');
	c = ft_strchr("Hello world",'f');
	printf("%s\n%s\n%s\n", a, b, c);
}*/	
