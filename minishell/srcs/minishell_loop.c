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

/**
 * @brief Handles the situation when no input prompt is received
 *
 * This function is called when the input prompt is null, indicating
 * that there was an issue with reading user input. It checks the `errno`
 * variable to determine the cause of the failure. If `errno` is not set,
 * it outputs "exit" to indicate a normal exit. If `errno` is set, it
 * prints an error message to standard error using `perror`, detailing the
 * issue encountered while reading input.
 *
 * @return Returns 1 to indicate that an error occurred
 */
static int	handle_null_prompt(void)
{
	if (!errno)
		write(2, "exit\n", 5);
	else
		perror("minishell: Error reading input");
	return (1);
}

/**
 * @brief Executes the parsed commands from user input
 *
 * This function handles the execution of commands that have been parsed
 * from the user's input. It checks for signal interruptions (e.g., Ctrl+C)
 * and proceeds with command execution only if no such signal was received.
 * The commands are lexically analyzed, parsed, expanded, and then executed
 * by calling the appropriate execution function. If a SIGINT signal is detected,
 * it sets the shell's status to indicate that the execution was interrupted.
 *
 * @param shell Pointer to the shell structure containing shell data and commands
 */
void	execute_commands(t_shell *shell)
{
	if (g_sig != SIGINT && lexer(shell))
	{
		shell->tab_cmd = parse_line(shell->trimmed_prompt);
		expand_str_cmd(shell->tab_cmd, shell->env_head, shell->status);
		rm_void_tab_cmd(shell->tab_cmd);
		mini_execute(shell, shell->tab_cmd);
	}
	if (g_sig == SIGINT)
		shell->status = 130;
}

/**
 * @brief Reads and processes user input from the terminal
 *
 * This function handles user input by setting up the prompt, reading
 * input via `readline`, and processing it if valid. It performs a check
 * to ensure the input is from an interactive terminal and updates the
 * environment variables if necessary. If the input is empty or interrupted
 * (e.g., by Ctrl+C), it handles these cases appropriately. Additionally,
 * it trims leading/trailing spaces from the prompt and adds it to the history.
 *
 * @param shell Pointer to the shell structure containing shell data and settings
 * @return Returns 1 if the input is from a non-tty or allocation failed,
 *         2 if memory allocation for trimmed prompt fails, and 0 on success
 */
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
		return (1);
	shell->prompt = readline(shell->terminal_prompt);
	if (!shell->prompt)
		return (handle_null_prompt());
	if (g_sig != SIGINT)
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
	g_sig = 0;
	rl_done = 0;
	free_in_loop(shell);
	delete_heredoc(shell->here_docs);
	shell->here_docs = NULL;
}

/**
 * @brief Main loop for executing shell commands
 *
 * This function runs the primary loop of the shell, where it configures
 * terminal settings, sets signal handlers, and repeatedly reads and processes
 * user input. Depending on the return value of `read_and_process_input`,
 * the loop either breaks (exit), continues (restart loop), or proceeds to
 * execute commands. After each command execution, cleanup is performed.
 * The loop only ends when an exit signal or condition is encountered.
 *
 * @param shell Pointer to the shell structure containing shell data and settings
 */
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
