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

#include "../../includes/minishell.h"

int	valid_exp(int c)
{
	if (c == '?' || c == '{' || ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

/**
 * @brief Handles single and double quotes in the input string.
 *
 * This function updates the state of quotation marks encountered in
 * the input string. It toggles the `in_squote` or `in_dquote` flags
 * based on whether a single quote or double quote is found and the 
 * other type of quote is not currently active. The index is incremented
 * to move past the quote character.
 *
 * @param input The input string being processed.
 * @param exp The expansion structure containing state information.
 * @return 0 if a quote is handled; 1 if no quote is present.
 */
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

/**
 * @brief Handles the exit status expansion for the variable.
 *
 * This function increments the index in the expansion structure,
 * converts the exit status to a string, and appends it to the
 * result buffer. If the conversion or appending fails, it returns 0.
 *
 * @param exp The expansion structure containing the state and result buffer.
 * @param status The exit status to be converted to a string and appended.
 * @return 1 on success, 0 on failure.
 */
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
