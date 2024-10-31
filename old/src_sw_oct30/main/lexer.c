/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:12:12 by yfan              #+#    #+#             */
/*   Updated: 2024/10/29 18:12:13 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	operator_quotes(char ch, int *in_squote, int *in_dquote)
{
	if (ch == '\'' && !(*in_dquote))
		*in_squote = !(*in_squote);
	else if (ch == '"' && !(*in_squote))
		*in_dquote = !(*in_dquote);
}

static int	is_operator_error(const char *input, int i)
{
	if (ft_strchr(OPERATOR, input[i]))
	{
		if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
			return (syntax_error('>'), TRUE);
		if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<')
			return (syntax_error('<'), TRUE);
		if (input[i] == '|' && input[i + 1] == '|')
			return (syntax_error('|'), TRUE);
		if (input[i] == '>' && input[i + 1] == '<')
			return (syntax_error('<'), TRUE);
		if (input[i] == '<' && input[i + 1] == '|')
			return (syntax_error('|'), TRUE);
	}
	return (FALSE);
}

static int	check_unclosed_quotes(int in_squote, int in_dquote)
{
	if (in_squote)
	{
		ft_putstr_fd(MES_SQUOTE_ERR, STDERR_FILENO);
		return (TRUE);
	}
	if (in_dquote)
	{
		ft_putstr_fd(MES_DQUOTE_ERR, STDERR_FILENO);
		return (TRUE);
	}
	return (FALSE);
}

int	wrong_operator_check(const char *input)
{
	int	in_squote;
	int	in_dquote;
	int	i;

	in_squote = FALSE;
	in_dquote = FALSE;
	i = 0;
	while (input[i])
	{
		operator_quotes(input[i], &in_squote, &in_dquote);
		if (!in_dquote && !in_squote && is_operator_error(input, i))
			return (TRUE);
		i++;
	}
	return (check_unclosed_quotes(in_squote, in_dquote));
}
