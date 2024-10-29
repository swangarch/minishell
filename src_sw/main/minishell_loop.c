#include "../includes/minishell.h"

static int handle_null_prompt()
{
	if (!errno)
		write(2, "exit\n", 5);
	else
		perror("minishell: Error reading input");
	return (1);
}

static int read_and_process_input(t_shell *shell)
{
	errno = 0;
	shell->terminal_prompt = join_prompt();
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
	return 0;
}

static void execute_commands(t_shell *shell)
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

static void post_execution_cleanup(t_shell *shell)
{
	g_sigint_flag = FALSE;
	rl_done = 0;
	free_in_loop(shell);
	delete_heredoc(shell->here_docs);
	shell->here_docs = NULL;
	// close(shell->std_fds[0]);//+++++++++++
	// close(shell->std_fds[1]);//+++++++++++++
}

void minishell_loop(t_shell *shell)
{
	int flag;
	configure_terminal(&shell->termios_set);
	while (1)
	{
		set_signal_handler();
		// shell->std_fds[0] = dup(STDIN_FILENO);
		// shell->std_fds[1] = dup(STDOUT_FILENO);
		// if (shell->std_fds[0] == -1 || shell->std_fds[1] == -1)
		// {
		// 	perror(MES_DUP_ERR);
		// 	exit(EXIT_FAILURE);
		// }
		flag = read_and_process_input(shell);
		if (flag == 1)
			break;
		else if (flag == 2)
			continue;
		execute_commands(shell);
		post_execution_cleanup(shell);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->termios_set);
}
