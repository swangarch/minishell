/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:47:09 by yfan              #+#    #+#             */
/*   Updated: 2024/05/28 18:51:11 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**ft_free(char **ptr, size_t idx)
{
	while (idx > 1 && ptr[idx - 2])
	{
		free(ptr[idx - 2]);
		ptr[idx - 2] = NULL;
		idx--;
	}
	free(ptr);
	ptr = NULL;
	return (NULL);
}

static int	ft_setstr(char **ptr, char const *s, char c, size_t *siz)
{
	while (*(s + *siz) && *(s + *siz) != c)
		(*siz)++;
	*ptr = ft_substr(s, 0, *siz);
	if (!(*ptr))
		return (0);
	return (1);
}

static size_t	ft_cnt_str(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	len;
	size_t	siz;

	if (!s)
		return (NULL);
	ptr = (char **)malloc((ft_cnt_str(s, c) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	len = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			siz = 0;
			if (!ft_setstr(&ptr[len++], s, c, &siz))
				return (ft_free(ptr, len));
			s += siz;
		}
	}
	ptr[len] = 0;
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	char	**ptr;
	char	test[] = "a1bc1def1gh";
	int	i;

	printf("origin string: %s\n", test);
	ptr = ft_split(test, '1');
	i = 0;
	while (ptr[i])
	{
		printf("after string: %s\n", ptr[i]);
		i++;
	}
	return (0);
}
*/
