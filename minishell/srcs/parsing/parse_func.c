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

#include "../../includes/minishell.h"

void	lst_add_back_strn(char *line, t_list **lst_token, int *i, int j)
{
	char	*token;

	token = NULL;
	token = ft_strndup(&line[*i], j);
	if (!token)
	{
		ft_lstadd_back(lst_token, NULL);
		return ;
	}
	ft_lstadd_back(lst_token, ft_lstnew(token));
	*i = *i + j - 1;
}

void	parse_word(char *line, t_list **lst_token, int *i)
{
	int		in_squote;
	int		in_dquote;
	int		j;

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
			return (lst_add_back_strn(line, lst_token, i, j), (void)0);
		else if (*i + j == (int)ft_strlen(line) - 1)
			return (lst_add_back_strn(line, lst_token, i, j + 1), (void)0);
		j++;
	}
}

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

static	void	destroy_tab_cmd(t_cmd **tab_cmd)
{
	int	i;

	i = 0;
	while (tab_cmd[i])
	{
		free_char_array(tab_cmd[i]->redin);
		free_char_array(tab_cmd[i]->redout);
		free_char_array(tab_cmd[i]->cmd);
		free(tab_cmd[i]);
		tab_cmd[i] = NULL;
		i++;
	}
	free(tab_cmd);
}

t_cmd	**parse_line(char *line)
{
	char	**tab_str;
	t_cmd	**tab_cmd;

	tab_str = split_ign_quote(line, '|');
	if (!tab_str)
		return (NULL);
	tab_cmd = create_cmd_tab(tab_str);
	if (!tab_cmd)
		return (free_char_array(tab_str), NULL);
	if (parse_error(tab_cmd))
	{
		destroy_tab_cmd(tab_cmd);
		free_char_array(tab_str);
		return (NULL);
	}
	free_char_array(tab_str);
	return (tab_cmd);
}
