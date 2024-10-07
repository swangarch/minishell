#include "../../includes/minishell.h"

void    configure_terminal(struct termios *termios_set)
{
    tcgetattr(0, termios_set);
    termios_set->c_lflag &= ~ECHOCTL;
    tcsetattr(0, TCSANOW, termios_set);
}

void    handle_sigint(int sig)
{
    if (sig == SIGINT)
    {
        g_ctrl_c = 1;
        write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void    set_signal_handler(void)
{
    struct sigaction sa_int, sa_quit;

    sa_int.sa_handler = handle_sigint;
    sa_int.sa_flags = SA_RESTART;
    sigemptyset(&sa_int.sa_mask);
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = SIG_IGN;
    sa_quit.sa_flags = SA_RESTART;
    sigemptyset(&sa_quit.sa_mask);
    sigaction(SIGQUIT, &sa_quit, NULL);
}
