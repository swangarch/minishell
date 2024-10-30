/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:15:02 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/28 14:08:52 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*lastc;

	lastc = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			lastc = (char *)s;
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	else
		return (lastc);
}
/*
#include <stdio.h>

int     main(void)
{
        const char      *a;
        const char      *b;
        const char      *c;
        a = ft_strrchr("Hello world",'l');
        b = ft_strrchr("Hello world",'\0');
        c = ft_strrchr("Hello world",'f');
        printf("%s\n%s\n%s\n", a, b, c);
}*/
