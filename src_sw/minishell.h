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
# define TRUE 1
# define FALSE 0


typedef struct	s_lstcmd
{
	t_list *full_cmd;
	t_list *redin;
	t_list *redout;
}	t_lstcmd;

typedef struct	s_strcmd
{
	char **redin;
	char **redout;
	char ***tab_cmd;
}	t_strcmd;

#define REDIN 1
#define HEREDOC 2
#define REDOUT 3
#define APPEND 4
#define TEXT 0


void    sigint_handler(int sig);
void    signals(void);
char	*ft_str3join(char *s1, char *s2, char *s3);
char	*ft_str4join(char *s1, char *s2, char *s3, char *s4);
char	*join_prompt(void);
void	minishell_loop(void);
void	parse_line(char *line);
int		lexer_check(char *line);

char	*ft_strndup(const char *s, int n);
void	ft_putstr(char *s);
char	*ft_strncpy(char *dest, char *src, unsigned int n);

void    ft_err(char *s);

int		is_red(char *s); //is redirection


void	print_tab(char **s);
void	print_lst(t_list *lst);
void	print_lst_partition(t_list **partition);


t_list	**partition_lst(t_list *lst_tk);
char	**lst_to_chatab(t_list *lst);
char	*lst_getstr(t_list *lst);

int		count_pipe(t_list *lst);
int		check_double_pipe(t_list *lst);
int		check_red_file(t_list *lst);
int		check_token_err(t_list *lst);

#endif
