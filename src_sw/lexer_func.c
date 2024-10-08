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
