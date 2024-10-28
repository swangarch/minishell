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

#include "../includes/minishell.h"

void expand_tab(char **tab, t_env *env_head, int status)
{
    int i;

    if (!tab)
        return;
    i = 0;
    while (tab[i])
    {
        tab[i] = expand_tilde(tab[i], env_head);
        tab[i] = expand_var(tab[i], env_head, status);
        i++;
    }
}

void expand_str_cmd(t_cmd **tab_cmd, t_env *env_head, int status)
{
    int i;

    if (!tab_cmd)
        return;
    i = 0;
    while (tab_cmd[i])
    {
        expand_tab(tab_cmd[i]->cmd, env_head, status);
        expand_tab(tab_cmd[i]->redin, env_head, status);
        expand_tab(tab_cmd[i]->redout, env_head, status);
        i++;
    }
}
