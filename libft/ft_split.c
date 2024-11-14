/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:17:01 by shuwang           #+#    #+#             */
/*   Updated: 2024/06/03 16:19:11 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_init(size_t *i, size_t *j, char const *s, char c)
{
	*i = 0;
	*j = 0;
	while (s[*i] && s[*i] == c)
	{
		(*j)++;
		(*i)++;
	}
}

static	int	c_word(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (s[i] != c && ft_strlen(s) != 0)
		count++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			count++;
		i++;
	}
	return (count);
}

static	char	*writestr(const char *s, char c, size_t i, size_t j)
{
	size_t		cn;
	char		*sstr;

	if (i + 1 == ft_strlen(s) && s[i] != c)
		i++;
	cn = 0;
	sstr = malloc(i - j + 1);
	if (sstr == NULL)
		return (NULL);
	while (j < i)
		sstr[cn++] = s[j++];
	sstr[cn] = '\0';
	return (sstr);
}

static	int	savetable(char **tabstr, char *sstr, size_t count)
{
	if (sstr == NULL)
	{
		while (count > 0)
		{
			free(tabstr[count - 1]);
			count--;
		}
		free(tabstr);
		return (-1);
	}
	else if (ft_strlen(sstr) != 0 && sstr)
	{
		tabstr[count] = sstr;
		count++;
	}
	else
	{
		free(sstr);
		sstr = NULL;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		j;
	int			count;
	char		**tabstr;

	count = 0;
	tabstr = malloc((c_word(s, c) + 1) * sizeof(char *));
	if (tabstr == NULL)
		return (NULL);
	ft_init(&i, &j, s, c);
	while (i < ft_strlen(s))
	{
		if (s[i] == c || i + 1 == ft_strlen(s))
		{
			count = savetable(tabstr, writestr(s, c, i, j), count);
			if (count == -1)
				return (NULL);
			j = i + 1;
		}
		i++;
	}
	tabstr[count] = NULL;
	return (tabstr);
}
/*
#include <stdio.h>

void	testsplit(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		printf("%s_", s[i]);
		i++;
	}
	printf("\n");
}
int	main(void)
{	
	//printf("%d\n", c_word(" Hello world  aq  my  friend i", ' '));
	//printf("%d\n", c_word("Hello   world    aq  my  friend i", ' '));
	//printf("%d\n", c_word("Hello world  aq  my  friend i", ' '));
	//printf("%d\n", c_word(" Hello world  aq  my  friend i ", ' '));
	//printf("%d\n", c_word("  Hello world  aq  my  friend i  ", ' '));
	//printf("%d\n", c_word("Hello world  aq  my  friend i", ' '));

	//testsplit(ft_split(" Hello world  aq  my  friend i", ' '));
        //testsplit(ft_split("Hello   world    aq  my  friend i", ' '));
        //testsplit(ft_split("Hello world  aq  my  friend i", ' '));
        //testsplit(ft_split(" Hello world  aq  my  friend i ", ' '));
        //testsplit(ft_split("  Hello world  aq  my  friend i  ", ' '));
        //testsplit(ft_split("Hello world  aq  my  friend i", ' '));
	//testsplit(ft_split("Hello", ' '));
	//testsplit(ft_split("Hello ", ' '));
	//testsplit(ft_split(" Hello", ' '));
	//testsplit(ft_split("     ", ' '));
	//testsplit(ft_split("", ' '));
	testsplit(ft_split("a", ' '));
	return (0);
}*/
