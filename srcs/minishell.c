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

int	g_sig;

/**
 * @brief Entry point for the minishell program
 *
 * This function initializes the shell environment, enters the main command loop,
 * and performs cleanup upon exit. It first checks that no command-line arguments
 * are passed, then initializes shell settings and environment variables,
 * enters the command processing loop, and finally frees resources and exits with
 * the shell's final status.
 *
 * @param ac Argument count, expected to be 1
 * @param av Argument vector, unused but checked for non-null
 * @param env Environment variables passed to initialize the shell
 * @return Returns 0 on successful execution
 */
int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	t_shell	*ptr;

	if (ac != 1 && av)
	{
		ft_putstr_fd(MES_ARG_NO_ONE, STDERR_FILENO);
		exit(EXIT_SUCCESS);
	}
	ptr = &shell;
	if (!ptr)
		return (1);
	init_shell(ptr, env);
	minishell_loop(ptr);
	free_before_exit(ptr);
	exit(shell.status);
	return (0);
}
