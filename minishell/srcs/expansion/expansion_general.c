/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_general.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:05:44 by yfan              #+#    #+#             */
/*   Updated: 2024/10/28 19:05:46 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_tab(char **tab, t_env *env_head, int status)
{
	int	i;

	if (!tab || !env_head)
		return ;
	i = 0;
	while (tab[i])
	{
		tab[i] = expand_tilde(tab[i], env_head);
		tab[i] = expand_var(tab[i], env_head, status);
		i++;
	}
}

void	expand_str_cmd(t_cmd **tab_cmd, t_env *env_head, int status)
{
	int	i;

	if (!tab_cmd || !env_head)
		return ;
	i = 0;
	while (tab_cmd[i])
	{
		expand_tab(tab_cmd[i]->cmd, env_head, status);
		expand_tab(tab_cmd[i]->redin, env_head, status);
		expand_tab(tab_cmd[i]->redout, env_head, status);
		i++;
	}
}

int	expand_var_here_check(char *input, t_expansion *exp, \
	t_env *lst_env, int status)
{
	if (input[exp->i] == '\'' && !exp->in_dquote)
	{
		exp->in_squote = !exp->in_squote;
		exp->result[exp->len++] = input[exp->i++];
	}
	else if (input[exp->i] == '"' && !exp->in_squote)
	{
		exp->in_dquote = !exp->in_dquote;
		exp->result[exp->len++] = input[exp->i++];
	}
	else if (input[exp->i] == '$' && valid_exp(input[exp->i + 1]))
	{
		if (!handle_dollar(input, exp, lst_env, status))
			return (1);
	}
	else
		exp->result[exp->len++] = input[exp->i++];
	return (0);
}
