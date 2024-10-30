/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:13:01 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/23 16:22:33 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	slen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	l;

	l = slen(s);
	write(fd, s, l);
	write(fd, "\n", 1);
}
/*
#include <fcntl.h>
int     main(void)
{
        char    *s = "haha NICE TO MEET YOU its good to see you";
        int     fd = open("test", O_RDWR);
        ft_putendl_fd(s, fd);
        close(fd);
        return (0);
}*/
