/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:24:03 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/23 17:01:42 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	l;
	char	r;

	l = n;
	if (l < 0)
	{
		write(fd, "-", 1);
		l = -l;
	}
	if (l > 9)
	{
		r = l % 10 + '0';
		l = l / 10;
		ft_putnbr_fd(l, fd);
		write(fd, &r, 1);
	}
	else
	{
		r = l + '0';
		write(fd, &r, 1);
	}
}
/*
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
int     main(int ac, char **av)
{
	(void)ac;
        int     fd = open("test", O_RDWR);
        ft_putnbr_fd(atoi(av[1]), fd);
        close(fd);
        return (0);
}*/
