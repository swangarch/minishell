/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:17:34 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/29 18:56:21 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0 || src == dest)
		return (dest);
	if (src > dest)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else if (src < dest)
	{
		i = n;
		while (i > 0)
		{
			((unsigned char *)dest)[i - 1] = ((unsigned char *)src)[i - 1];
			i--;
		}
	}
	return (dest);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char	src[50] = {1,2,3,4,5,6,7};
	char	dest[50] = {11,14,15,16,17,28,19};
	printf("%s\n", (char *)memmove(dest, src, 11));
	printf("%s\n", (char *)ft_memmove(dest, src, 11));
	char    src1[50] = {97,98,99,100,101,102,103};
        char    dest1[50] = {66,67,68,69,70,71,72};
        printf("%s\n", (char *)memmove(dest1, src1, 11));
        printf("%s\n", (char *)ft_memmove(dest1, src1, 11));
	char    Result[50] = {97,98,99,100,101,102,103,104,105};
        printf("%s\n", (char *)memmove(Result + 2, Result, 3));
        printf("%s\n", (char *)ft_memmove(Result + 2, Result, 3));
	printf("%s\n", (char *)memmove(Result + 1, Result, 3));
        printf("%s\n", (char *)ft_memmove(Result + 1, Result, 3));
	printf("%s\n", (char *)memmove(Result + 3, Result, 3));
        printf("%s\n", (char *)ft_memmove(Result + 3, Result, 3));
	printf("%s\n", (char *)memmove(Result + 3, Result, 0));
        printf("%s\n", (char *)ft_memmove(Result + 3, Result, 0));
	char    Resultb[50] = {97,98,99,100,101,102,103};
        printf("%s\n", (char *)memmove(Resultb, Resultb, 3));
        printf("%s\n", (char *)ft_memmove(Resultb, Resultb, 3));
        return (0);
}*/
