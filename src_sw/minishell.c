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
//void	parse_prompt(char *line);


void	check_line(char *line)
{
	if (!line && errno)
	{
		//perror.....
		printf("Error\n");//////////////
		exit(0);
	}
	if (!line && !errno)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
}

void	minishell_loop(void)
{
	char *line = NULL;
	char *prompt;

	while (1)
	{
		prompt = join_prompt();
		line = readline(prompt);

		add_history(line);

		check_line(line);
		lexer_check(line);
		parse_line(line);
		free(line);
	}
}
