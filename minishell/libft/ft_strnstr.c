/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:41:21 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/30 20:55:38 by shuwang          ###   ########.fr       */
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

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (slen(little) == 0)
		return ((char *)big);
	while (big[i] && (i < len))
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] \
				&& big[i + j] && (i + j) < len)
			j++;
		if (j == slen(little))
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	*big = "Hello world my friend";
	char	*little = "rl";
	int	num = 10;

	printf("%s\n",ft_strnstr(big, little, num));
	printf("%s\n",ft_strnstr("ababdabtevdabe", "abe", 20));
	//printf("%s\n",strnstr(big, little, num));
	return (0);
}*/
