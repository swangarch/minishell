/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:58:20 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/25 16:58:21 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	in_quote(char c, int *in_dquote, int *in_squote)
{
	if (c == '\'' && !(*in_dquote))
		(*in_squote) = !(*in_squote);
	else if (c == '\"' && !(*in_squote))
		(*in_dquote) = !(*in_dquote);
}

static	int	count_word(char const *s, char c)
{
	size_t	i;
	size_t	count;
	int		in_squote;
	int		in_dquote;

	in_dquote = 0;
	in_squote = 0;
	i = 0;
	count = 0;
	if (s[i] && s[i] != c)
	{
		in_quote(s[i], &in_dquote, &in_squote);
		count++;
	}
	while (s[i])
	{
		in_quote(s[i], &in_dquote, &in_squote);
		if (s[i] == c && s[i + 1] != c && s[i + 1] && !in_dquote && !in_squote)
			count++;
		i++;
	}
	return (count);
}

static	int	copy_word(char const *s, char **tabstr, t_split *v, char c)
{
	v->j = 0;
	while (s[v->i + v->j])
	{
		in_quote(s[v->i + v->j], &v->ind, &v->ins);
		if ((s[v->i + v->j] == c || !s[v->i + v->j + 1]) && !v->ind && !v->ins)
		{
			if (!s[v->i + v->j + 1])
				tabstr[v->c] = ft_strndup(&s[v->i], v->j + 1);
			else
				tabstr[v->c] = ft_strndup(&s[v->i], v->j);
			if (!tabstr[v->c])
			{
				free_char_array(tabstr);
				return (0);
			}
			(v->c)++;
			while (s[v->i + v->j + 1] && s[v->i + v->j + 1] == c)
				(v->j)++;
			v->i = v->i + v->j;
			break ;
		}
		v->j++;
	}
	return (1);
}

char	**split_ign_quote(char const *s, char c)
{
	char	**tabstr;
	t_split	v;

	v.c = 0;
	v.i = 0;
	v.j = 0;
	v.ind = 0;
	v.ins = 0;
	tabstr = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!tabstr)
		return (NULL);
	while (s[v.i] == c)
		(v.i)++;
	while (s[v.i])
	{
		if (!copy_word(s, tabstr, &v, c))
			return (NULL);
		v.i++;
	}
	tabstr[v.c] = NULL;
	return (tabstr);
}
