/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:04:02 by shuwang           #+#    #+#             */
/*   Updated: 2024/06/03 19:04:09 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_ptf(int n, int count)
{
	char	r;
	long	l;

	l = n;
	if (l < 0)
	{
		write(1, "-", 1);
		l = -l;
		count++;
	}
	if (l > 9)
	{
		r = l % 10 + '0';
		l = l / 10;
		count = ft_putnbr_ptf(l, count + 1);
		write(1, &r, 1);
	}
	else if (l >= 0 && l <= 9)
	{
		r = l + '0';
		write(1, &r, 1);
		count++;
	}
	return (count);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d\n", ft_putnbr_ptf(-12345678, 0));
	return (0);
}*/
