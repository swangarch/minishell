#include "../includes/minishell.h"

char    *expand_buffer(char *old_buffer, int *size)
{
    int     new_size;
    char    *new_buffer;
    
    new_size = (*size) * FACTOR;
    new_buffer = (char *)malloc(new_size * sizeof(char));
    if (!new_buffer)
    {
        free(old_buffer);
        return (NULL);
    }
    ft_memcpy(new_buffer, old_buffer, *size);
    free(old_buffer);
    *size = new_size;
    return (new_buffer);
}

int     append_str(t_expansion *exp)
{
    int str_len;
    
    str_len = ft_strlen(exp->exit_status);
    while (exp->len + str_len >= exp->size)
    {
        exp->result = expand_buffer(exp->result, &exp->size);
        if (!exp->result)
            return (free(exp->exit_status), 0);
    }
    ft_strlcpy(exp->result + exp->len, exp->exit_status, exp->size);
    exp->len += str_len;
    free(exp->exit_status);
    exp->exit_status = NULL;
    return (1);
}

int     append_env(t_expansion *exp)
{
    int str_len;
    
    str_len = ft_strlen(exp->env_val);
    while (exp->len + str_len >= exp->size)
    {
        exp->result = expand_buffer(exp->result, &exp->size);
        if (!exp->result)
            return (free(exp->env_val), 0);
    }
    ft_strlcpy(exp->result + exp->len, exp->env_val, exp->size);
    exp->len += str_len;
    free(exp->env_val);
    exp->env_val = NULL;
    return (1);
}

int     init_expansion(t_expansion *exp)
{
    exp->size = INIT_SIZE;
    exp->result = (char *)malloc(exp->size * sizeof(char));
    if (!exp->result)
        return (0);
    exp->len = 0;
    exp->i = 0;
    exp->k = 0;
    exp->in_squote = 0;
    exp->in_dquote = 0;
    exp->exit_status = NULL;
    exp->env_val = NULL;
    return (1);
}

int     valid_exp(int c)
{
    if (c == '?' || c == '{' || ft_isalnum(c) || c == '_')
        return (1);
    return (0);
}

char    *expand_var(char *input, t_env *lst_env, int status)
{
    t_expansion exp;

    if (!init_expansion(&exp))
        return (free(input), NULL);
    while (input[exp.i] != '\0')
    {
        if (input[exp.i] == '\'' && !exp.in_dquote)
        {
            exp.in_squote = !exp.in_squote;
            exp.i++;
        }
        else if (input[exp.i] == '"' && !exp.in_squote)
        {
            exp.in_dquote = !exp.in_dquote;
            exp.i++;
        }
        else if (input[exp.i] == '$' && !exp.in_squote && valid_exp(input[exp.i + 1]))
        {
            exp.i++;
            if (input[exp.i] == '?')
            {
                exp.i++;
                exp.exit_status = ft_itoa(status);
                if (!exp.exit_status || !append_str(&exp))
                    return (free(input), free(exp.result), NULL);
            }
            else if (ft_isdigit(input[exp.i]))
                exp.i++;
            else if (input[exp.i] == '{')
            {
                exp.i++;
                exp.k = 0;
                while (input[exp.i] && input[exp.i] != '}')
                    exp.var_name[exp.k++] = input[exp.i++];
                exp.var_name[exp.k] = '\0';
                if (input[exp.i] == '}')
                    exp.i++;
                if (!ft_strcmp(exp.var_name, "?"))
                {
                    exp.exit_status = ft_itoa(status);
                    if (!exp.exit_status || !append_str(&exp))
                        return (free(input), free(exp.result), NULL);
                }
                else
                {
                    exp.env_val = mini_get_env(exp.var_name, lst_env);
                    if (!exp.env_val || !append_env(&exp))
                        return (free(input), free(exp.result), NULL);
                }
            }
            else if (ft_isalnum(input[exp.i]) || input[exp.i] == '_')
            {
                exp.k = 0;
                while (ft_isalnum(input[exp.i]) || input[exp.i] == '_')
                    exp.var_name[exp.k++] = input[exp.i++];
                exp.var_name[exp.k] = '\0';
                if (exp.k > 0)
                {
                    exp.env_val = mini_get_env(exp.var_name, lst_env);
                    if (!exp.env_val || !append_env(&exp))
                        return (free(input), free(exp.result), NULL);
                }
            }
        }
        else
            exp.result[exp.len++] = input[exp.i++];
        if (exp.len >= exp.size)
        {
            exp.result = expand_buffer(exp.result, &exp.size);
            if (!exp.result)
                return (free(input), NULL);
        }
    }
    exp.result[exp.len] = '\0';
    return (free(input), exp.result);
}

int	    ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

char    *expand_tilde(char *input, t_env *lst_env)
{
    char    *home;
    char    *result;

    if (input[0] == '~')
    {
        if (!input[1] || input[1] == '/')
        {
            home = mini_get_env("HOME", lst_env);
            if (!home)
                return (free(input), NULL);
            if (!input[1])
                return (free(input), home);
            if (input[1] == '/')
            {
                result = ft_strjoin(home, input + 1);
                return (free(input), free(home), result);
            }
        }
    }
    return (input);
}
