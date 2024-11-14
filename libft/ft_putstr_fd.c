/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:41:27 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/23 16:20:25 by shuwang          ###   ########.fr       */
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

void	ft_putstr_fd(char *s, int fd)
{
	int	l;

	l = slen(s);
	write(fd, s, l);
}
/*
#include <fcntl.h>
int	main(void)
{
	char	*s = "haha NICE TO MEET YOU iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii";
	int	fd = open("test", O_RDWR);
	ft_putstr_fd(s, fd);
	close(fd);
	return (0);
}*/
