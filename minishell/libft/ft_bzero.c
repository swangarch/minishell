/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:32:45 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/21 17:58:04 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}
/*
#include <stdio.h>
void    *ft_memset(void *s, int c, size_t n)
{
        unsigned char   *p;
        size_t                  i;

        i = 0;
        p = (unsigned char *)s;
        while (i < n)
        {
                p[i] = (unsigned char)c;
                i++;
        }
        return (s);
}

int	main(void)
{
	
	size_t	i = 0;
	size_t	n = 35;
	unsigned char	memory1[100];
	void	*ptr =  memory1;

	ptr = ft_memset(ptr, 'a', n);
	ft_bzero(ptr,5);
	while (i < n)
	{
		if (((unsigned char *)ptr)[i] == 0)
			printf("backslash\n");
		else
			printf("%c\n", ((unsigned char *)ptr)[i]);	
		i++;
	}	
	return (0);	
}*/
