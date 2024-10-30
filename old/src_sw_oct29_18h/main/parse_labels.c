/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_labels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:46:33 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/08 12:46:35 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_red(char *s)
{
	if (!s)
		return (-1);
	if (!strcmp(s, "<"))
		return (REDIN);
	if (!strcmp(s, "<<"))
		return (HEREDOC);
	if (!strcmp(s, ">"))
		return (REDOUT);
	if (!strcmp(s, ">>"))
		return (APPEND);
	return (TEXT);
}

void	lst_add_back_str(char *s, t_list **lst_token)
{
	char	*token;

	token = NULL;
	token = ft_strdup(s);
	if (!token)
	{
		ft_lstadd_back(lst_token, NULL);
		return ;
	}
	ft_lstadd_back(lst_token, ft_lstnew(token));
}

void	parse_symbol_single(char *line, t_list **lst_token, int i)
{
	char	*token;

	if (!line)
		return ;
	token = NULL;
	if (line[i] == '>')
		lst_add_back_str(">", lst_token);
	if (line[i] == '<')
		lst_add_back_str("<", lst_token);
	if (line[i] == '|')
		lst_add_back_str("|", lst_token);
}

void	parse_symbol_double(char *line, t_list **lst_token, int *i)
{
	char	*token;

	if (!line)
		return ;
	token = NULL;
	if (!ft_strncmp(line + *i, ">>", 2))
		token = ft_strdup(">>");
	else if (!ft_strncmp(line + *i, "<<", 2))
		token = ft_strdup("<<");
	ft_lstadd_back(lst_token, ft_lstnew(token));
	(*i)++;
}

int	is_wordchar(char c)
{
	if (c == '\0')
		return (0);
	if (c == ' ' || c == '>' || c == '<' || c == '|')
		return (0);
	return (1);
}
