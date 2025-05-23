/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_here.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:58:09 by yfan              #+#    #+#             */
/*   Updated: 2024/10/29 17:58:10 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_var_here(char *input, t_env *lst_env, int status)
{
	t_expansion	exp;

	if (!input)
		return (NULL);
	if (!init_expansion(&exp))
		return (free(input), NULL);
	while (input[exp.i] != '\0')
	{
		if (expand_var_here_check(input, &exp, lst_env, status))
			return (free(input), free(exp.result), NULL);
		if (exp.len >= exp.size && !handle_buffer(&exp))
			return (free(input), NULL);
	}
	exp.result[exp.len] = '\0';
	return (free(input), exp.result);
}

char	*expand_buffer(char *old_buffer, int *size)
{
	int		new_size;
	char	*new_buffer;

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

/**
 * @brief Appends the exit status string to the expansion result buffer.
 *
 * This function checks if there is enough space in the result buffer
 * to append the exit status string. If not, it expands the buffer
 * accordingly. After appending, it updates the length of the result
 * and frees the memory allocated for the exit status string.
 *
 * @param exp Pointer to the t_expansion structure containing the
 *            result buffer and exit status.
 * @return 1 on success; 0 on failure (if memory allocation fails).
 */
int	append_str(t_expansion *exp)
{
	int	str_len;

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

/**
 * @brief Appends the environment variable value to the expansion result buffer.
 *
 * This function checks if there is enough space in the result buffer
 * to append the environment variable value. If not, it expands the buffer
 * as needed. After appending, it updates the length of the result
 * and frees the memory allocated for the environment variable value.
 *
 * @param exp Pointer to the t_expansion structure containing the
 *            result buffer and environment variable value.
 * @return 1 on success; 0 on failure (if memory allocation fails).
 */
int	append_env(t_expansion *exp)
{
	int	str_len;

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

int	init_expansion(t_expansion *exp)
{
	if (!exp)
		return (0);
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
