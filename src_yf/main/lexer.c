#include "../includes/minishell.h"

int lexer(t_shell *shell)
{
    if (ft_strlen(shell->trimmed_prompt) == 0 || \
        is_empty_line_passed(shell) == TRUE)
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
            in_squote = !in_squote;
        else if (input[i] == '"' && !in_squote)
            in_dquote = !in_dquote;
        if (!in_dquote && !in_squote)
        {
            if (ft_strchr(OPERATOR, input[i]))
            {
                if (input[i] == '>' && input[i + 1] == '>' \
                    && input[i + 2] == '>')
                    return (syntax_error('>'), TRUE);
                if (input[i] == '<' && input[i + 1] == '<' \
                    && input[i + 2] == '<')
                    return (syntax_error('<'), TRUE);
                if (input[i] == '|' && input[i + 1] == '|')
                    return (syntax_error('|'), TRUE);
                if (input[i] == '>' && input[i + 1] == '<')
                    return (syntax_error('<'), TRUE);
                if (input[i] == '<'&& input[i + 1] == '|')
                    return (syntax_error('|'), TRUE);
            }
        }
        i++;
    }
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

int is_empty_line_passed(t_shell *s)
{
    if (s->trimmed_prompt[0] == '~' && ft_strlen(s->trimmed_prompt) == 1)
    {
        s->status = 126;
        ft_putstr_fd(SHELL "~ " ISDIR "\n", STDERR_FILENO);
        return (TRUE);
    }
    if (s->trimmed_prompt[0] == DQUOTE && s->trimmed_prompt[1] == DQUOTE \
        && ft_strlen(s->trimmed_prompt) == 2)
    {
        ft_putstr_fd(SHELL CMD_NOT_FND "\n", STDERR_FILENO);
        s->status = 127;
        return (TRUE);
    }
    if (s->trimmed_prompt[0] == SQUOTE && s->trimmed_prompt[1] == SQUOTE \
        && ft_strlen(s->trimmed_prompt) == 2)
    {
        ft_putstr_fd(SHELL CMD_NOT_FND "\n", STDERR_FILENO);
        s->status = 127;
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
