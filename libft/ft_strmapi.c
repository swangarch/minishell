/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:37:01 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/22 10:38:50 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	slen(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*s1;

	i = 0;
	s1 = malloc(slen(s) + 1);
	if (s1 == NULL)
		return (NULL);
	while (s[i])
	{
		s1[i] = (*f)(i, s[i]);
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
/*
#include <stdio.h>
char	test(unsigned int i, char c)
{
	return (i + c);
}
#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_strmapi("Hello world", &test));
	return (0);
}*/
