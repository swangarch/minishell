/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:40:30 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/28 18:32:30 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	swmin(size_t a, size_t b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

static	int	slen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	if (siz <= i)
		return (siz + slen((char *)src));
	while (src[j] && (i + j < siz - 1))
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (slen((char *)src) + swmin(siz, i));
}
/*
#include <stdio.h>
int	main(void)
{
	char	stra[34] = "Hello world ";
	char	*strb = "my friend, how are you";

	printf("%zu\n", ft_strlcat(stra, strb, 34));
	printf("%s\n", stra);
	return (0);	
}*/	
