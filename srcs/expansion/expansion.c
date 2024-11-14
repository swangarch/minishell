/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:05:38 by yfan              #+#    #+#             */
/*   Updated: 2024/10/29 18:05:40 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_variable(char *input, t_expansion *exp, t_env *lst_env)
{
	exp->k = 0;
	while (ft_isalnum(input[exp->i]) || input[exp->i] == '_')
		exp->var_name[exp->k++] = input[exp->i++];
	exp->var_name[exp->k] = '\0';
	if (exp->k > 0)
	{
		if (!handle_env_var(exp, lst_env))
			return (0);
	}
	return (1);
}

int	handle_dollar(char *input, t_expansion *exp, t_env *lst_env, int status)
{
	exp->i++;
	if (input[exp->i] == '?')
	{
		if (!handle_exit_status(exp, status))
			return (0);
	}
	else if (ft_isdigit(input[exp->i]))
		exp->i++;
	else if (input[exp->i] == '{')
	{
		if (!handle_braces(input, exp, lst_env, status))
			return (0);
	}
	else if (ft_isalnum(input[exp->i]) || input[exp->i] == '_')
	{
		if (!handle_variable(input, exp, lst_env))
			return (0);
	}
	return (1);
}

int	handle_buffer(t_expansion *exp)
{
	exp->result = expand_buffer(exp->result, &exp->size);
	if (!exp->result)
		return (0);
	return (1);
}

char	*expand_var(char *input, t_env *lst_env, int status)
{
	t_expansion	exp;

	if (!input || !lst_env)
		return (NULL);
	if (!init_expansion(&exp))
		return (free(input), NULL);
	while (input[exp.i] != '\0')
	{
		if (!handle_quotes(input, &exp))
			continue ;
		else if (input[exp.i] == '$' && !exp.in_squote \
			&& valid_exp(input[exp.i + 1]))
		{
			if (!handle_dollar(input, &exp, lst_env, status))
				return (free(input), free(exp.result), NULL);
		}
		else
			exp.result[exp.len++] = input[exp.i++];
		if (exp.len >= exp.size && !handle_buffer(&exp))
			return (free(input), NULL);
	}
	exp.result[exp.len] = '\0';
	return (free(input), exp.result);
}

char	*expand_tilde(char *input, t_env *lst_env)
{
	char	*home;
	char	*result;

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
