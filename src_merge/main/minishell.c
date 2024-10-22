/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:05:24 by yfan              #+#    #+#             */
/*   Updated: 2024/09/27 17:05:28 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_sigint_flag;

int main(int ac, char **av, char **env)
{
    t_shell shell;

    if (ac != 1 && av)
    {
        ft_putstr_fd(MES_ARG_NO_ONE, STDERR_FILENO);
        exit(EXIT_SUCCESS);
    }
    init_shell(&shell, env);
    minishell_loop(&shell);
    free_before_exit(&shell);
    exit(shell.status);
    return (0);
}
