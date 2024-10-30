/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:16:54 by yfan              #+#    #+#             */
/*   Updated: 2024/10/29 18:16:57 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_null_prompt(void)
{
	if (!errno)
		write(2, "exit\n", 5);
	else
		perror("minishell: Error reading input");
	return (1);
}

void	execute_commands(t_shell *shell)
{
	if (!g_sigint_flag && lexer(shell))
	{
		shell->tab_cmd = parse_line(shell->trimmed_prompt);
		expand_str_cmd(shell->tab_cmd, shell->env_head, shell->status);
		mini_execute(shell, shell->tab_cmd);
	}
	if (g_sigint_flag)
		shell->status = 130;
}

static int	read_and_process_input(t_shell *shell)
{
	if (!isatty(STDIN_FILENO))
	{
		check_tty(shell);
		return (1);
	}
	errno = 0;
	shell->terminal_prompt = join_prompt();
	if (!shell->terminal_prompt)
		return (2);
	shell->prompt = readline(shell->terminal_prompt);
	if (!shell->prompt)
		return (handle_null_prompt());
	if (!g_sigint_flag)
	{
		shell->trimmed_prompt = ft_strtrim(shell->prompt, SPACES);
		if (!shell->trimmed_prompt)
			return (free_2_char(shell->terminal_prompt, shell->prompt), 2);
		if (ft_strlen(shell->trimmed_prompt))
			add_history(shell->prompt);
		update_env(shell);
	}
	return (0);
}

static void	post_execution_cleanup(t_shell *shell)
{
	g_sigint_flag = FALSE;
	rl_done = 0;
	free_in_loop(shell);
	delete_heredoc(shell->here_docs);
	shell->here_docs = NULL;
}

void	minishell_loop(t_shell *shell)
{
	int	flag;

	configure_terminal(&shell->termios_set);
	while (1)
	{
		set_signal_handler();
		flag = read_and_process_input(shell);
		if (flag == 1)
			break ;
		else if (flag == 2)
			continue ;
		execute_commands(shell);
		post_execution_cleanup(shell);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->termios_set);
}
