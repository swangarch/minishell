/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:57:13 by yfan              #+#    #+#             */
/*   Updated: 2024/10/28 18:57:15 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	valid_exp(int c)
{
	if (c == '?' || c == '{' || ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	handle_quotes(char *input, t_expansion *exp)
{
	if (input[exp->i] == '\'' && !exp->in_dquote)
	{
		exp->in_squote = !exp->in_squote;
		exp->i++;
		return (0);
	}
	else if (input[exp->i] == '"' && !exp->in_squote)
	{
		exp->in_dquote = !exp->in_dquote;
		exp->i++;
		return (0);
	}
	return (1);
}

int	handle_exit_status(t_expansion *exp, int status)
{
	exp->i++;
	exp->exit_status = ft_itoa(status);
	if (!exp->exit_status || !append_str(exp))
		return (0);
	return (1);
}

int	handle_env_var(t_expansion *exp, t_env *lst_env)
{
	exp->env_val = mini_get_env(exp->var_name, lst_env);
	if (!exp->env_val || !append_env(exp))
		return (0);
	return (1);
}

int	handle_braces(char *input, t_expansion *exp, t_env *lst_env, int status)
{
	exp->i++;
	exp->k = 0;
	while (input[exp->i] && input[exp->i] != '}')
		exp->var_name[exp->k++] = input[exp->i++];
	exp->var_name[exp->k] = '\0';
	if (input[exp->i] != '}')
		return (0);
	else
		exp->i++;
	if (!ft_strcmp(exp->var_name, "?"))
	{
		if (!handle_exit_status(exp, status))
			return (0);
	}
	else
	{
		if (!handle_env_var(exp, lst_env))
			return (0);
	}
	return (1);
}
