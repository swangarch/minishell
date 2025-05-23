/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:18:25 by yfan              #+#    #+#             */
/*   Updated: 2024/10/29 15:18:27 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_single_builtin(t_shell *shell, t_cmd **tab_cmd)
{
	int	type_cmd;

	type_cmd = is_build_in(tab_cmd[0]->cmd[0]);
	if (type_cmd)
	{
		if (!redir(tab_cmd[0], shell, 0))
		{
			delete_heredoc(shell->here_docs);
			shell->here_docs = NULL;
			shell->status = 1;
			return (1);
		}
		shell->status = mini_builtin(type_cmd, shell, NULL, 0);
		delete_heredoc(shell->here_docs);
		shell->here_docs = NULL;
		dup2(shell->std_fds[0], STDIN_FILENO);
		dup2(shell->std_fds[1], STDOUT_FILENO);
		return (1);
	}
	return (0);
}

static int	cmd_loop(int *num, int *p_fd, t_shell *shell, t_cmd **tab_cmd)
{
	pid_t	pid;
	int		type_cmd;

	type_cmd = is_build_in(tab_cmd[num[1]]->cmd[0]);
	pid = fork();
	if (num[1] == num[0] - 1)
		shell->pid = pid;
	if (pid == -1)
		return (shell->status = 3, perror(SHELL "fork"), free(p_fd), 1);
	else if (pid == 0)
	{
		set_signal_child();
		set_close(shell->std_fds);
		set_child(num, p_fd, shell, tab_cmd[num[1]]);
		if (type_cmd)
		{
			shell->status = mini_builtin(type_cmd, shell, p_fd, num[1]);
			free_before_exit(shell);
			free(p_fd);
			exit(shell->status);
		}
		execute(tab_cmd[num[1]]->cmd, shell, p_fd);
	}
	return (0);
}

static void	wait_for_children(int num_cmd, int *p_fd, t_shell *shell)
{
	int		term_sig;
	int		i;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	close_multi_fd(num_cmd, p_fd);
	i = -1;
	while (++i < num_cmd)
	{
		pid = waitpid(-1, &term_sig, 0);
		if (pid == shell->pid)
			shell->status = term_sig;
	}
	if ((shell->status & 0x7F) != 0)
	{
		term_sig = shell->status & 0x7F;
		shell->status = 128 + term_sig;
		if (term_sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		if (term_sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}
	else if ((shell->status & 0x7F) == 0 && ((shell->status >> 8) & 0xFF) != 0)
		shell->status = (shell->status >> 8) & 0xFF;
}

/**
 * @brief Executes a sequence of commands, handling built-ins and pipes.
 *
 * Checks for valid command and shell pointers, processes here-docs,
 * and handles single built-in commands. Initializes pipe file descriptors,
 * executes each command in a loop using `cmd_loop`, and waits for all
 * child processes to finish. Cleans up resources, including here-docs
 * and pipe file descriptors.
 *
 * @param shell Pointer to the shell structure containing environment and status.
 * @param tab_cmd Array of command structures to execute.
 */
void	mini_execute(t_shell *shell, t_cmd **tab_cmd)
{
	int	num[2];
	int	*p_fd;

	if (!tab_cmd || !shell)
		return (shell->status = 2, (void)0);
	num[0] = get_cmdtab_num(tab_cmd);
	shell->here_docs = process_heredocs(tab_cmd, shell, num[0]);
	if (!shell->here_docs)
		return ;
	if (num[0] == 1 && handle_single_builtin(shell, tab_cmd))
		return ;
	if (init_pipe_fds(&p_fd, num[0], shell))
		return ;
	num[1] = -1;
	while (++(num[1]) < num[0])
		if (cmd_loop(num, p_fd, shell, tab_cmd))
			return (free(p_fd), (void)0);
	wait_for_children(num[1], p_fd, shell);
	free(p_fd);
	delete_heredoc(shell->here_docs);
	shell->here_docs = NULL;
}

/**
 * @brief Executes a command after resolving its path and checking its validity.
 *
 * If the command is empty, the function exits with a success status. 
 * It retrieves the command's path, checks if it exists, and verifies
 * whether it's a directory. If the command is a directory, an error message
 * is printed, and the process exits with an error status. Otherwise, it 
 * proceeds to execute the command using `final_execute`.
 *
 * @param cmd Array of command arguments, where cmd[0] is the command to execute.
 * @param shell Pointer to the shell structure containing environment and status.
 * @param p_fd Array of pipe file descriptors for inter-process communication.
 */
void	execute(char **cmd, t_shell *shell, int *p_fd)
{
	char		*path;
	struct stat	cmd_stat;

	if (!cmd[0][0])
	{
		free_save_line(shell, p_fd, NULL);
		exit(0);
	}
	path = get_path(cmd[0], shell, p_fd);
	if (!path)
	{
		ft_put3str_fd(SHELL, cmd[0], COMMAND_NO, STDERR_FILENO);
		free_save_line(shell, p_fd, NULL);
		exit(127);
	}
	if (stat(path, &cmd_stat) == 0 && (cmd_stat.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_put3str_fd(SHELL, path, MES_IS_DIR, STDERR_FILENO);
		free_save_line(shell, p_fd, path);
		exit(126);
	}
	final_execute(shell, path, cmd, p_fd);
}
