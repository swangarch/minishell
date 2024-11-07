/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:26:26 by yfan              #+#    #+#             */
/*   Updated: 2024/10/29 18:26:27 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	configure_terminal(struct termios *termios_set)
{
	struct termios	new_termios;

	tcgetattr(STDIN_FILENO, termios_set);
	new_termios = *termios_set;
	new_termios.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
		rl_done = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
	}
}

int	event(void)
{
	return (0);
}

void	set_signal_handler(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
	rl_event_hook = event;
}

void	set_signal_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	//signal(SIGPIPE, SIG_IGN);
}
