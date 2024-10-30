/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:33:32 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/22 10:34:59 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	slen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = 0;
	j = 0;
	s = malloc(slen(s1) + slen(s2) + 1);
	if (s == NULL)
		return (NULL);
	while (i < slen(s1))
	{
		s[i] = s1[i];
		i++;
	}
	while (j < slen(s2))
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	return (s);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_strjoin("Hello ", "World!"));
	return (0);
}*/
