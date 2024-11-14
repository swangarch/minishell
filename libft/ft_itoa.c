/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:13:40 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/21 15:20:34 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sw_cl(int n)
{
	int		c;
	long	l;

	c = 0;
	l = n;
	if (n < 0)
	{
		c++;
		l = -l;
	}
	while (l > 9)
	{
		l = l / 10;
		c++;
	}
	c++;
	return (c);
}

char	*ft_itoa(int n)
{
	int		cl;
	char	*nstr;
	long	l;

	l = n;
	cl = sw_cl(n);
	nstr = malloc(cl + 1);
	if (nstr == NULL)
		return (NULL);
	nstr[cl] = '\0';
	cl--;
	if (l < 0)
	{
		nstr[0] = '-';
		l = -l;
	}
	while (l > 9)
	{
		nstr[cl] = l % 10 + '0';
		l = l / 10;
		cl--;
	}
	nstr[cl] = l + '0';
	return (nstr);
}
/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("%s\n", ft_itoa(atoi(argv[1])));
	}
	return (0);
}
*/
