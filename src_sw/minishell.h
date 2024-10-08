/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:26:37 by shuwang           #+#    #+#             */
/*   Updated: 2024/09/24 15:26:55 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"
# include "termios.h"
# include "errno.h"

# define BLACK "\001\033[30m\002"
# define RED "\001\033[31m\002"
# define RED_B "\001\033[1;31m\002"
# define GREEN "\001\033[32m\002"
# define YELLOW "\001\033[33m\002"
# define BLUE "\001\033[34m\002"
# define BLUE_B "\001\033[1;34m\002"
# define PURPLE "\001\033[35m\002"
# define CYAN "\001\033[36m\002"
# define WHITE "\001\033[37m\002"
# define WHITE_B "\001\033[1;37m\002"
# define COLOR_END "\001\033[0m\002"
//# define YELLOW_STRVAR(str_var) YELLOW str_var COLOR_END

# define PATH_MAX 4096

# define ERR_PREF "minishell: "

void    sigint_handler(int sig);
void    signals(void);
char	*ft_str3join(char *s1, char *s2, char *s3);
char	*ft_str4join(char *s1, char *s2, char *s3, char *s4);
char	*join_prompt(void);
void	minishell_loop(void);
void	parse_line(char *line);
int		lexer_check(char *line);

char	*ft_strndup(const char *s, int n);

void    ft_err(char *s);

#endif
