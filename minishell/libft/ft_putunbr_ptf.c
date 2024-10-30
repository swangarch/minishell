/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:02:02 by shuwang           #+#    #+#             */
/*   Updated: 2024/06/03 19:02:08 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunbr_ptf(unsigned int n, int count)
{
	char	r;

	if (n > 9)
	{
		r = n % 10 + '0';
		n = n / 10;
		count = ft_putunbr_ptf(n, count + 1);
		write(1, &r, 1);
	}
	else if (n <= 9)
	{
		r = n + '0';
		write(1, &r, 1);
		count++;
	}
	return (count);
}
