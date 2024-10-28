#include "../includes/minishell.h"

void configure_terminal(struct termios *termios_set)
{
    struct termios new_termios;

    tcgetattr(STDIN_FILENO, termios_set);
    new_termios = *termios_set;
    new_termios.c_lflag |= ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void handle_sigint(int sig)
{
    if (sig == SIGINT)
    {
        g_sigint_flag = TRUE;
        rl_done = 1;
        write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        // rl_replace_line("", 0);
        // rl_redisplay();
    }
}

int	event(void)
{
	return (0);
}

void set_signal_handler()
{
    struct sigaction    sa_int;
    struct sigaction    sa_quit;

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
