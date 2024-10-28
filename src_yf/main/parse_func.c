/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:54:29 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/02 16:54:30 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lst_add_back_strn(char *line, t_list **lst_token, int *i, int j)
{
	char *token;

	token = NULL;
	token = ft_strndup(&line[*i], j);
	if (!token)
	{
		ft_lstadd_back(lst_token, NULL);
		return ;
	}
	ft_lstadd_back(lst_token, ft_lstnew(token));//protect??
	*i = *i + j - 1;
}

void	parse_word(char *line, t_list **lst_token, int *i)
{
	int		in_squote;
	int		in_dquote;
	int		j;
	char	*token;

	in_squote = 0;
	in_dquote = 0;
	j = 0;
	while (line[*i + j])
	{
		if (line[*i + j] == '\'' && !in_dquote)
			in_squote = !in_squote;
		if (line[*i + j] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		if (!is_wordchar(line[*i + j]) && !in_squote && !in_dquote)
		{
			lst_add_back_strn(line, lst_token, i, j);
			return ;
		}
		else if (*i + j == (int)ft_strlen(line) - 1)
		{
			lst_add_back_strn(line, lst_token, i, j + 1);
			return ;
		}
		j++;
	}
}

// void	parse_word(char *line, t_list **lst_token, int *i)
// {
// 	int		in_squote;
// 	int		in_dquote;
// 	int		j;
// 	char	*token;

// 	in_squote = 0;
// 	in_dquote = 0;
// 	j = 0;
// 	while (line[*i + j])
// 	{
// 		if (line[*i + j] == '\'' && !in_dquote)
// 			in_squote = !in_squote;
// 		if (line[*i + j] == '\"' && !in_squote)
// 			in_dquote = !in_dquote;
// 		if (!is_wordchar(line[*i + j]) && !in_squote && !in_dquote)
// 		{
// 			token = ft_strndup(&line[*i], j);//protect
// 			ft_lstadd_back(lst_token, ft_lstnew(token));//protect
// 			*i = *i + j - 1;
// 			return ;
// 		}
// 		else if (*i + j == (int)ft_strlen(line) - 1)
// 		{
// 			token = ft_strndup(&line[*i], j + 1);//protect
// 			ft_lstadd_back(lst_token, ft_lstnew(token));//protect
// 			*i = *i + j;
// 			return ;
// 		}
// 		j++;
// 	}
// }

t_list	*tokenize_line(char *line)
{
	int		i;
	t_list	*lst_token;

	if (!line)
		return (NULL);
	lst_token = NULL;
	i = 0;
	if (!ft_strlen(line))
		return (NULL);
	while (line[i])
	{
		if (!ft_strncmp(&line[i], ">>", 2) || !ft_strncmp(&line[i], "<<", 2))
			parse_symbol_double(line, &lst_token, &i);
		else if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			parse_symbol_single(line, &lst_token, i);
		else if (is_wordchar(line[i]))
			parse_word(line, &lst_token, &i);
		i++;
	}
	return (lst_token);
}

t_cmd	**parse_line(char *line)  //protected++++++++++++++++++
{	
	char **tab_str;
	t_cmd **tab_cmd;

	//tab_str = ft_split(line, '|');
	tab_str = split_ign_quote(line, '|');
	if (!tab_str)
		return (NULL);
	tab_cmd = create_cmd_tab(tab_str);
	if (!tab_cmd || parse_error(tab_cmd))
	{
		free_char_array(tab_str);
		return (NULL);
	}
	return(tab_cmd);
}