/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:03:09 by yfan              #+#    #+#             */
/*   Updated: 2024/10/28 19:03:12 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	lexer(t_shell *shell)
{
	if (shell->trimmed_prompt && (ft_strlen(shell->trimmed_prompt) == 0 \
		|| is_empty_line_passed(shell) == TRUE))
		return (FALSE);
	else if (wrong_operator_check(shell->trimmed_prompt) == TRUE)
	{
		shell->status = 2;
		return (FALSE);
	}
	else if (bad_pipe(shell) == TRUE)
		return (FALSE);
	return (TRUE);
}

int	is_empty_line_passed(t_shell *s)
{
	if (s->trimmed_prompt[0] == '~' && ft_strlen(s->trimmed_prompt) == 1)
	{
		s->status = 126;
		ft_putstr_fd(SHELL "~ " ISDIR "\n", STDERR_FILENO);
		return (TRUE);
	}
	if (s->trimmed_prompt[0] == DQUOTE \
		&& s->trimmed_prompt[1] == DQUOTE && ft_strlen(s->trimmed_prompt) == 2)
	{
		ft_putstr_fd(SHELL CMD_NOT_FND "\n", STDERR_FILENO);
		s->status = 127;
		return (TRUE);
	}
	if (s->trimmed_prompt[0] == SQUOTE \
		&& s->trimmed_prompt[1] == SQUOTE && ft_strlen(s->trimmed_prompt) == 2)
	{
		ft_putstr_fd(SHELL CMD_NOT_FND "\n", STDERR_FILENO);
		s->status = 127;
		return (TRUE);
	}
	return (FALSE);
}

int	bad_pipe(t_shell *shell)
{
	int	len;

	len = ft_strlen(shell->trimmed_prompt) - 1;
	if (shell->trimmed_prompt[0] == '|')
	{
		shell->status = 2;
		return (syntax_error('|'), TRUE);
	}
	else if (shell->trimmed_prompt[len] == '|' \
		|| shell->trimmed_prompt[len] == '>' \
		|| shell->trimmed_prompt[len] == '<')
	{
		shell->status = 2;
		return (syntax_error_newline(), TRUE);
	}
	return (FALSE);
}
