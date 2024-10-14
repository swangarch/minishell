/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:01:31 by shuwang           #+#    #+#             */
/*   Updated: 2024/09/24 15:23:59 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
# include "libft.h"
# include "termios.h"
# include "errno.h"
 
int		sig_recieved;  //用来free

void	minishell_loop(void);

char	*get_username()
{
	return (getenv("USER"));
}

char	*ft_str3join(char *s1, char *s2, char *s3)
{
	char	*temp1;
	//char	*temp2;
	char	*result;

	temp1 = ft_strjoin(s1, s2);//protect
	result = ft_strjoin(temp1, s3);
	free(temp1);
	return (result);
}

char	*ft_str4join(char *s1, char *s2, char *s3, char *s4)
{
	char	*temp1;
	char	*temp2;
	char	*result;

	temp1 = ft_strjoin(s1, s2);//protect
	temp2 = ft_strjoin(temp1, s3);
	free(temp1);
	result = ft_strjoin(temp2, s4);
	free(temp2);
	return (result);
}

char	*text_color(char *s, int color)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;
	char	*result;
	char	*color_char;

	color_char = ft_itoa(color); ///////////protect
	temp1 = ft_strjoin("\001\033[", color_char);   ////////////protect
	free(color_char);  //////////////////protect
	temp2 = ft_strjoin(temp1, "m\002");
	free(temp1);//////
	temp3 = ft_strjoin(temp2, s);
	free(temp2);
	result = ft_strjoin(temp3, "\001\033[0m\002");
	free(temp3);/////////////////////
	return (result);
}

void	parse_prompt(char *line)
{
	if (!strcmp(line, "exit"))
			exit(0);
}

int		lexer_check(char *line)
{
	if (!strcmp(line, "test"))
		return (1);
	return (0);
}

char	*join_prompt(void)//(char *s1, char *s2, char *s3)
{
	return (ft_str4join(RED_B "yf&sw" COLOR_END, WHITE_B "@" COLOR_END, BLUE_B "minishell❄" COLOR_END, " "));
	//return (ft_strjoin(text_color("yf&sw", 31), text_color("minishell❀", 33)));
	//return (ft_strjoin("yf&sw", "minishell:"));
}

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
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}


void	minishell_loop(void)
{
	char *line = NULL;
	char *prompt;

	while (1)
	{
		prompt = join_prompt();
		line = readline(prompt);
		//if (errno == EINTR)
		//{
		//	printf("flag error!\n");
		//	continue ;
		//}
		if (!line && errno)
		{
			//perror.....
			printf("Error\n");
			exit(0);
		}
		if (!line && !errno)
		{
			exit(0);
		}

		lexer_check(line);
		parse_prompt(line);
		free(line);
	}
}

int	main(int ac, char **av)
{
	struct termios termios_settings;

	tcgetattr(STDIN_FILENO, &termios_settings);
	termios_settings.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_settings);

	(void) av;
	if (ac > 1)
	{
		printf("More than one argument is given\n");
		return (1);
	}

	signals();
	minishell_loop();

	return (0);
}
