/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:33:23 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/28 18:47:36 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	slen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;

	i = 0;
	if (siz == 0)
		return (slen(src));
	while (i < siz - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (slen(src));
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	const char	*src = "Hello world how are you";
	char	dst[100];
	size_t	n;

	n = 10;
	printf("%lu\n%s\n", ft_strlcpy(dst, src, n), dst);
}*/
