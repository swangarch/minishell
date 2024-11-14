/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:13:18 by shuwang           #+#    #+#             */
/*   Updated: 2024/07/22 15:13:48 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		diff;

	diff = 0;
	i = 0;
	while (s1[i] || s2[i])
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
#include <string.h>
int main(int ac, char **av)
{
    ft_printf("%d\n%d\n", ft_strcmp(av[1], av[2]), strcmp(av[1], av[2]));
    return (0);
}*/