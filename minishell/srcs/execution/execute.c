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
		if (!red_in(tab_cmd[0], shell, 0) || !red_out(tab_cmd[0]))
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
	if (pid == -1)
		return (shell->status = 3, perror(SHELL "fork"), free(p_fd), 1);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
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
	int	term_sig;
	int	i;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	i = 0;
	while (i < 2 * (num_cmd - 1))
		close(p_fd[i++]);
	i = -1;
	while (++i < num_cmd)
		waitpid(-1, &shell->status, 0);
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
