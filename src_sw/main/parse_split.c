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

#include "../includes/minishell.h"

// static	int	slen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// void	free_char_array(char **array)
// {
// 	int	i;

// 	if (array == NULL)
// 		return ;
// 	i = 0;
// 	while (array[i] != NULL)
// 	{
// 		free(array[i]);
// 		i++;
// 	}
// 	free(array);
// }

// char	*ft_strndup(const char *s, int n)
// {
// 	char	*dup;
// 	int		i;
// 	int	len;
// 	int	s_len;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	s_len = slen(s);
// 	if (n < s_len)
// 		len = n;
// 	else
// 		len = s_len;
// 	dup = malloc(len + 1);
// 	if (dup == NULL)
// 		return (NULL);
// 	while (s[i] && i < n)
// 	{
// 		dup[i] = s[i];
// 		i++;
// 	}
// 	dup[i] = '\0';
// 	return (dup);
// }

// void print_tab(char **tab)
// {
//     int i = 0;

//     if (!tab)
//         return ;
//     while (tab[i])
//     {
//         puts(tab[i]);
//         i++;
//     }
// }

// int     count_word(char const *s, char c)
// {
// 	size_t	i;
// 	size_t	count;
//     int in_squote;
//     int in_dquote;

//     in_dquote = 0;
//     in_squote = 0;
// 	i = 0;
// 	count = 0;
// 	if (s[i] && s[i] != c)
//     {
//         if (s[i] == '\'' && !in_dquote)
//             in_squote = !in_squote;
//         else if (s[i] == '\"' && !in_squote)
//             in_dquote = !in_dquote;
//         count++;
//     }
// 	while (s[i])
// 	{
//         if (s[i] == '\'' && !in_dquote)
//             in_squote = !in_squote;
//         else if (s[i] == '\"' && !in_squote)
//             in_dquote = !in_dquote;
// 		if (s[i] == c && s[i + 1] != c && s[i + 1] && !in_dquote && !in_squote)
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// char	**split_ign_quote(char const *s, char c)
// {
//     char **tabstr;
//     size_t	count = 0;
//     int i = 0;
//     int j = 0;
//     int in_squote;
//     int in_dquote;

//     in_dquote = 0;
//     in_squote = 0;
//     tabstr = malloc(sizeof(char *) * (count_word(s, c) + 1));//////////////////////////
//     if (!tabstr)
//         return (NULL);
//     while(s[i] == c)
//         i++;
//     while(s[i])
//     {
//         j = 0;
//         while (s[i + j])
//         {
//             if (s[i + j] == '\'' && !in_dquote)
//             in_squote = !in_squote;
//             else if (s[i + j] == '\"' && !in_squote)
//             in_dquote = !in_dquote;
//             if ((s[i + j] == c || !s[i + j + 1]) && !in_dquote && !in_squote)
//             {
//                 if (s[i + j] == c)
//                     tabstr[count] = ft_strndup(&s[i], j);
//                 else
//                     tabstr[count] = ft_strndup(&s[i], j + 1);
//                 if (!tabstr[count])
//                 {
//                     free_char_array(tabstr);
//                     return (NULL);
//                 }
//                 count++;
//                 while (s[i + j + 1] && s[i + j + 1] == c)
//                     j++;
//                 i = i + j;
//                 break ;
//             }
//             j++;
//         }
//         i++;
//     }
//     tabstr[count] = NULL;
//     return (tabstr);
// }

static void     in_quote(char c, int *in_dquote, int *in_squote)
{
    if (c == '\'' && !(*in_dquote))
        (*in_squote) = !(*in_squote);
    else if (c == '\"' && !(*in_squote))
        (*in_dquote) = !(*in_dquote);
}

static int     count_word(char const *s, char c)
{
	size_t	i;
	size_t	count;
    int in_squote;
    int in_dquote;

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

static int    copy_word(char const *s, char **tabstr, t_split *v, char c)
{
    v->j = 0;
    while (s[v->i + v->j])
    {
        in_quote(s[v->i + v->j], &v->ind, &v->ins);
        if ((s[v->i + v->j] == c || !s[v->i + v->j + 1]) && !v->ind && !v->ins)
        {
            if (!s[v->i + v->j  + 1])
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
    char **tabstr;
    t_split v;

    v.c = 0;
    v.i = 0;
    v.j = 0;
    v.ind = 0;
    v.ins = 0;
    tabstr = malloc(sizeof(char *) * (count_word(s, c) + 1));
    if (!tabstr)
        return (NULL);
    while(s[v.i] == c)
        (v.i)++;
    while(s[v.i])
    {
        if (!copy_word(s, tabstr, &v, c))
            return (NULL);
        v.i++;
    }
    tabstr[v.c] = NULL;
    return (tabstr);
}

// int main(int ac, char **av)
// {
//     char **tab;
//     if (ac > 1)
//     {
//         tab = split_ign_quote(av[1], '|');
//         printf("the number of command is %d\n", count_word(av[1], '|'));
//         //tab = "dgd | "kd|'|'djl" "|'dhkjh|'"";
//         print_tab(tab);
//         free_char_array(tab);
//     }
//     return (0);
// }


// static	void	ft_init(size_t *i, size_t *j, int *count)
// {
// 	*i = 0;
// 	*j = 0;
// 	*count = 0;
// }

// static	int	c_word(char const *s, char c)
// {
// 	size_t	i;
// 	size_t	count;

// 	i = 0;
// 	count = 0;
// 	if (s[i] != c && ft_strlen(s) != 0)
// 		count++;
// 	while (s[i])
// 	{
// 		if (s[i] == c && s[i + 1] != c && s[i + 1])
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// static	char	*writestr(const char *s, char c, size_t i, size_t j)
// {
// 	size_t		cn;
// 	char		*sstr;

// 	if (i + 1 == ft_strlen(s) && s[i] != c)
// 		i++;
// 	cn = 0;
// 	sstr = malloc(i - j + 1);
// 	if (sstr == NULL)
// 		return (NULL);
// 	while (j < i)
// 		sstr[cn++] = s[j++];
// 	sstr[cn] = '\0';
// 	return (sstr);
// }

// static	int	savetable(char **tabstr, char *sstr, size_t count)
// {
// 	if (sstr == NULL)
// 	{
// 		while (count > 0)
// 		{
// 			free(tabstr[count - 1]);
// 			count--;
// 		}
// 		free(tabstr);
// 		return (-1);
// 	}
// 	else if (ft_strlen(sstr) != 0 && sstr)
// 	{
// 		tabstr[count] = sstr;
// 		count++;
// 	}
// 	else
// 	{
// 		free(sstr);
// 		sstr = NULL;
// 	}
// 	return (count);
// }

// char	**ft_split(char const *s, char c)
// {
// 	size_t		i;
// 	size_t		j;
// 	int			count;
// 	char		**tabstr;

// 	ft_init(&i, &j, &count);
// 	tabstr = malloc((c_word(s, c) + 1) * sizeof(char *));
// 	if (tabstr == NULL)
// 		return (NULL);
// 	while (s[i] && s[i++] == c)
// 		j++;
// 	while (i < ft_strlen(s))
// 	{
// 		if (s[i] == c || i + 1 == ft_strlen(s))
// 		{
// 			count = savetable(tabstr, writestr(s, c, i, j), count);
// 			if (count == -1)
// 				return (NULL);
// 			j = i + 1;
// 		}
// 		i++;
// 	}
// 	tabstr[count] = NULL;
// 	return (tabstr);
// }
