/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:18:43 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/28 18:46:07 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		diff;

	diff = 0;
	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] == s2[i])
			i++;
		else
		{
			diff = (unsigned char)s1[i] \
				- (unsigned char)s2[i];
			break ;
		}
	}
	return (diff);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d\n", ft_strncmp("Hello worldC", "Hello worldcup", 20));
	return (0);
}*/
