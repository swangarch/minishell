/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:42:34 by shuwang           #+#    #+#             */
/*   Updated: 2024/06/03 18:39:52 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	uintptr_t	slen(char *base)
{
	uintptr_t	i;

	i = 0;
	while (base[i])
		i++;
	return (i);
}

static	int	ft_ptr_base(uintptr_t n, char *base, int count)
{
	char	r;

	if (n >= slen(base))
	{
		r = base[n % slen(base)];
		n = n / slen(base);
		count = ft_ptr_base(n, base, count + 1);
		write(1, &r, 1);
	}
	else if (n < slen(base))
	{
		write(1, &base[n], 1);
		count++;
	}
	return (count);
}

int	ft_putptr_ptf(void *p)
{
	uintptr_t	pnum;
	int			count;

	if (p == NULL)
	{
		ft_putstr_ptf("(nil)");
		return (5);
	}
	pnum = (uintptr_t)p;
	ft_putstr_ptf("0x");
	count = 2;
	count = count + ft_ptr_base(pnum, "0123456789abcdef", 0);
	return (count);
}
/*
int	main(void)
{
	ft_ptr_base(12125, "0123456789abcdef");
	write(1, "\n", 1);
	ft_ptr_base(0, "0123456789abcdef");
	write(1, "\n", 1);
	ft_ptr_base((unsigned long)-1, "0123456789abcdef");
	write(1, "\n", 1);

	ft_ptr_base(12125, "0123456789");
	write(1, "\n", 1);
        ft_ptr_base(0, "0123456789");
	write(1, "\n", 1);
        ft_ptr_base((unsigned long)-1, "0123456789");
	write(1, "\n", 1);
	ft_ptr_base(99999, "0123456789");
        write(1, "\n", 1);
        ft_ptr_base(1009, "0123456789");
        write(1, "\n", 1);
        ft_ptr_base(9, "0123456789");
        write(1, "\n", 1);

	char	*str = "Hello world";

	ft_putptr(str);
	write(1, "\n", 1);
	ft_ptr_base((uintptr_t)str, "0123456789");
	write(1, "\n", 1);
	ft_ptr_base((uintptr_t)str, "0123456789abcdef");
	write(1, "\n", 1);
}*/
