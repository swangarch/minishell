/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:14:54 by shuwang           #+#    #+#             */
/*   Updated: 2024/06/03 19:15:09 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned	int	slen(char *base)
{
	unsigned int	i;

	i = 0;
	while (base[i])
		i++;
	return (i);
}

static	int	ft_unint_base(unsigned int n, char *base, int count)
{
	char	r;

	if (n >= slen(base))
	{
		r = base[n % slen(base)];
		n = n / slen(base);
		count = ft_unint_base(n, base, count + 1);
		write(1, &r, 1);
	}
	else if (n < slen(base))
	{
		write(1, &base[n], 1);
		count++;
	}
	return (count);
}

int	ft_putx_ptf(unsigned int n, char c)
{
	int	count;

	count = 0;
	if (c == 'x')
		count = ft_unint_base(n, "0123456789abcdef", 0);
	else if (c == 'X')
		count = ft_unint_base(n, "0123456789ABCDEF", 0);
	return (count);
}
