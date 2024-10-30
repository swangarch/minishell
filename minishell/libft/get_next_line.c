/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:25:52 by shuwang           #+#    #+#             */
/*   Updated: 2024/06/18 14:49:05 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*lst_get_line(t_clist **lst, int i, int count, char *str)
{
	t_clist	*curr;
	t_clist	*freenode;

	if (*lst == NULL)
		return (NULL);
	curr = *lst;
	count = lst_count_nlorend(*lst);
	str = malloc(count + 1);
	if (!str)
	{
		ft_lstclear_gnl(lst);
		return (NULL);
	}
	curr = *lst;
	while (i < count)
	{
		str[i] = curr->content;
		freenode = curr;
		curr = curr->next;
		free(freenode);
		i++;
	}
	*lst = curr;
	str[i] = '\0';
	return (str);
}

char	*read_line(int fd, int readnum, char *fbuf)
{
	static t_clist	*lst[FD_MAX];

	if (lst[fd] && lst_find_nl(lst[fd]))
		return (lst_get_line(&lst[fd], 0, 0, NULL));
	fbuf = malloc(BUFFER_SIZE * sizeof(char));
	if (!fbuf)
	{
		ft_lstclear_gnl(&lst[fd]);
		return (NULL);
	}
	while (readnum > 0)
	{
		readnum = read(fd, fbuf, BUFFER_SIZE);
		copy_tolist(&lst[fd], fbuf, readnum);
		if (lst[fd] == NULL || lst_find_nl(lst[fd]))
		{
			free(fbuf);
			return (lst_get_line(&lst[fd], 0, 0, NULL));
		}
	}
	free(fbuf);
	if (readnum < 0)
		ft_lstclear_gnl(&lst[fd]);
	return (lst_get_line(&lst[fd], 0, 0, NULL));
}

char	*get_next_line(int fd)
{
	char	*fbuf;

	fbuf = NULL;
	if (fd == -1 || fd > FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	return (read_line(fd, 1, fbuf));
}
/*
#include <stdio.h>

void    ft_putstr(char *s)
{
    int i;

    i = 0;
    if (s == NULL)
    {
        write(1, "(null)", 6);
        return ;
    }
    while (s[i])
    {
        write(1, &s[i], 1);
        i++;
    }
}

int	main(int ac, char **av)
{
	int	fd;
    	int	i = 0;
	char	*str;

	if (ac == 3)
	{
		fd = open(av[1], O_RDONLY);
        	while (i < atoi(av[2]))
        	{
			printf("The %d line —————————— \n", i);
			str = get_next_line(fd);
			ft_putstr(str);
			free(str);
			i++;
		}
        }
	return (0);
}*/
