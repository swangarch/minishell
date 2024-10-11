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

int		sig_flag;

void	minishell_loop(void);



char	*get_username()
{
	return (getenv("USER"));
}

char	*text_color(char *s, int color)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;
	char	*result;
	char	*color_char;

	color_char = ft_itoa(color); ///////////protect
	temp1 = ft_strjoin("\033[", color_char);   ////////////protect
	free(color_char);  //////////////////protect
	temp2 = ft_strjoin(temp1, "m");
	free(temp1);//////
	temp3 = ft_strjoin(temp2, s);
	free(temp2);
	result = ft_strjoin(temp3, "\033[0m");
	free(temp3);/////////////////////
	return (result);
}

char	*ft_str4join(char *s1, char *s2, char *s3, char *s4)
{
	char	*temp1;
	char	*temp2;
	char	*result;

	temp1 = ft_strjoin(s1, s2);
	temp2 = ft_strjoin(temp1, s3);
	free(temp1);
	result = ft_strjoin(temp2, s4);
	free(temp2);
	return (result);
}

void	parse_prompt(char *line)
{
	//printf("The prompt is %s\n", line);

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
	return (ft_str4join(text_color("shuwang", 31), text_color("@", 0),text_color("paul ", 34),text_color("minishell:", 33)));
}

void sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit(0);
	}
}

void sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		signal(SIGINT, &sigint_handler);
	}
}

void	minishell_loop(void)
{
	char *line;
	char *prompt;

	while (1)
	{
		prompt = join_prompt();
		line = readline(prompt);
		if (!line)
			printf("Fail to read");

		lexer_check(line);
		parse_prompt(line);
		free(line);
	}
}

int	main(int ac, char **av)
{
	(void) av;
	if (ac > 1)
	{
		printf("More than one argument is given\n");
		return (1);
	}

	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, &sigquit_handler);
	minishell_loop();

	return (0);
}
