/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:15:32 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/20 19:28:05 by shuwang          ###   ########.fr       */
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

char	*ft_strndup(const char *s, int n)
{
	char	*dup;
	int		i;
	int	len;
	int	s_len;

	i = 0;
	s_len = slen(s);
	if (n < s_len)
		len = n;
	else
		len = s_len;
	dup = malloc(s_len + 1);
	if (dup == NULL)
		return (NULL);
	while (s[i] && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*str = "Hello world";
	char	*strdup = ft_strndup(str, 15);
	
	printf("%s\n%s\n", str, strdup);
	//free(str);
	free(strdup);
	return (0);
}*/
