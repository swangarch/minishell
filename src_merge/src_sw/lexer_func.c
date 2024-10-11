/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:54:38 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/02 16:54:39 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int     check_quote(char *line)
{
    int i;
    int j;
    int s_quote_ok;
    int d_quote_ok;

    i = 0;
    s_quote_ok = 1;
    d_quote_ok = 1;
    while (line[i])
    {
        if (line[i] == '\'')
        {
            j = 1;
            s_quote_ok = 0;
            if (line[i + 1] && line[i + 1] == '\'')
                break ;

            while (line[i + j])
            {
                if (line[i + j] == '\'')
                {
                    s_quote_ok = 1;
                    i = i + j;
                    break ;
                }
                j++;
            }
        }
        if (line[i] == '\"')
        {
            j = 1;
            d_quote_ok = 0;
            if (line[i + 1] && line[i + 1] == '\"')
                break ;
            while (line[i + j])
            {
                if (line[i + j] == '\"')
                {
                    d_quote_ok = 1;
                    i = i + j;
                    break ;
                }
                j++;
            }
        }
        i++;
    }
    if (s_quote_ok && d_quote_ok)
    {
        //printf(ERR_PREF "Quote OK\n");
        return (1);
    }
    else
    {
        printf(ERR_PREF "Unclosed quote error\n");
        return (0);
    }
}


int     check_redirection(char *line)
{
    int i;
    int j;

    i = 0;
    if (!ft_strcmp(line, "~"))
    {
        ft_err(ERR_PREF);
        ft_err(getenv("HOME"));
        ft_err(": Is a directory\n");
        return (1);
    }
    while (line[i])
    {
        if (line[i] == '\'')
        {
            j = 1;
            while (line[i + j])
            {
                if (line[i + j] == '\'')
                {
                    i = i + j;
                    break ;
                }
                j++;
            }
        }
        if (line[i] == '\"')
        {
            j = 1;
            while (line[i + j])
            {
                if (line[i + j] == '\"')
                {
                    i = i + j;
                    break ;
                }
                j++;
            }
        }
        if (line[i] == '>')
        {
            if (line[i + 1] && line[i + 1] == '>')
            {
                if (line[i + 2] && line[i + 2] == '>')
                {
                    ft_err(ERR_PREF "syntax error near unexpected token `>'\n");
                    return (1);
                }
                i++;
            }
            if (line[i + 1] && line[i + 1] == '<')
            {
                ft_err(ERR_PREF "syntax error near unexpected token `<'\n");
                return (1);
                i++;
            }
        }
        if (line[i] == '<')
        {
            if (line[i + 1] && line[i + 1] == '<')
            {
                if (line[i + 2] && line[i + 2] == '<')
                {
                    ft_err(ERR_PREF "syntax error near unexpected token `<'\n");
                    return (1);
                }
                i++;
            }
        }
        if (line[i] == '|')
        {
            if (line[i + 1] && line[i + 1] == '|')
            {
                ft_err(ERR_PREF "syntax error near unexpected token `|'\n");
                return (1);
            }
        }
        i++;
    }
    return (0);
}

/*
int 	syntax_error(char c)
{
    printf("%s%s `%c'\n", SHELL, SYN_ERR, c);
	return (TRUE);
}

int 	syntax_error_newline(void)
{
    printf("%s%s\n", SHELL, SYN_ERR_NEWLINE);
	return (TRUE);
}

int wrong_operator_check(const char *input)
{
    int in_squote;
    int in_dquote;
    int i;

    in_squote = FALSE;
    in_dquote = FALSE;
    i = 0;
    while (input[i])
    {
        if (input[i] == '\'' && !in_dquote)
        {
            in_squote = !in_squote;
        }
        else if (input[i] == '"' && !in_squote)
        {
            in_dquote = !in_dquote;
        }
        if (!in_dquote && !in_squote)
        {
            if (ft_strchr(OPERATOR, input[i]))
            {
                if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
                {
                    syntax_error('>');
                    return (TRUE);
                }
                if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<')
                {
                    syntax_error('<');
                    return (TRUE);
                }
                if (input[i] == '|' && input[i + 1] == '|')
                {
                    syntax_error('|');
                    return (TRUE);
                }
                if (input[i] == '>' && input[i + 1] == '<')
                {
                    syntax_error('<');
                    return (TRUE);
                }
                if (input[i] == '<'&& input[i + 1] == '|')
                {
                    syntax_error('|');
                    return (TRUE);
                }
            }
        }
        i++;
    }
    if (in_squote)
    {
        printf(MES_SQUOTE_ERR);
        return TRUE;
    }
    if (in_dquote)
    {
        printf(MES_DQUOTE_ERR);
        return TRUE;
    }
    return (FALSE);
}

int is_empty_line_passed(t_shell *s)
{
    if (s->trimmed_prompt[0] == '~' && ft_strlen(s->trimmed_prompt) == 1)
    {
        s->exit_code = 126;
        printf(SHELL "~ " ISDIR "\n");
        return (TRUE);
    }
    if (s->trimmed_prompt[0] == DQUOTE && s->trimmed_prompt[1] == DQUOTE && ft_strlen(s->trimmed_prompt) == 2)
    {
        printf(SHELL CMD_NOT_FND "\n");
        s->cmd_has_been_executed = FALSE;
        s->exit_code = 127;
        return (TRUE);
    }
    if (s->trimmed_prompt[0] == SQUOTE && s->trimmed_prompt[1] == SQUOTE && ft_strlen(s->trimmed_prompt) == 2)
    {
        printf(SHELL CMD_NOT_FND "\n");
        s->cmd_has_been_executed = FALSE;
        s->exit_code = 127;
        return (TRUE);
    }
    return (FALSE);
}

int bad_pipe(t_shell *shell)
{
    int len;

    len = ft_strlen(shell->trimmed_prompt) - 1;
    if (shell->trimmed_prompt[0] == '|')
    {
        shell->exit_code = 2;
        return (syntax_error('|'), TRUE);
    }
    else if (shell->trimmed_prompt[len] == '|' || shell->trimmed_prompt[len] == '>' || shell->trimmed_prompt[len] == '<')
    {
        shell->exit_code = 2;
        return (syntax_error_newline(), TRUE);
    }
    return (FALSE);
}

int lexer(t_shell *shell)
{
    if (ft_strlen(shell->trimmed_prompt) == 0 || is_empty_line_passed(shell) == TRUE)
        return (FALSE);
    else if (wrong_operator_check(shell->trimmed_prompt) == TRUE)
    {
        shell->exit_code = 2;
        shell->cmd_has_been_executed = FALSE;
        return (FALSE);
    }
    else if (bad_pipe(shell) == TRUE)
        return (FALSE);
    return (TRUE);
}*/

int		lexer_check(char *line)
{
    char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " ");
    if (!trimmed_line)
    {
        return (-1);
    }
	check_quote(trimmed_line);
    check_redirection(trimmed_line);
	return (0);
}
