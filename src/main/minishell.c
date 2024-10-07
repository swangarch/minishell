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

#include "../../includes/minishell.h"

int g_ctrl_c;

int main(int ac, char **av, char **env)
{
    t_shell shell;

    if (ac != 1 && av)
    {
        printf(RED MES_ARG_NO_ONE COLOR_E);
        exit(EXIT_SUCCESS);
    }
    init_shell(&shell, env);
    minishell_loop(&shell);
    free_before_exit(&shell);
    exit(shell.exit_code);
    return (0);
}
