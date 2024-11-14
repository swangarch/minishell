/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:58:51 by shuwang           #+#    #+#             */
/*   Updated: 2024/06/01 18:02:37 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	*dest[100];
	char	*src = "Hello world, how are you";
	void	*vdest = (void *)dest;
	void	*vsrc = (void *)src;

	ft_memcpy(vdest, vsrc, 20);
	//(char)dest[10] = '\0';
	printf("%s\n", (char *)vdest);
	printf("Mine: %s\n", (char *)ft_memcpy(NULL, NULL, 3));
	//printf("Real: %s\n", (char *)memcpy(NULL, NULL , 3));
	return (0);
}*/
