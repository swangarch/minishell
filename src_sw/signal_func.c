/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:33:21 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/02 16:33:23 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		signal(SIGINT, &sigint_handler);
	}
}

void signals(void)
{
	struct termios termios_settings;

	tcgetattr(STDIN_FILENO, &termios_settings);
	termios_settings.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_settings);

	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
