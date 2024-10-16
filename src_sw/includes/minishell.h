/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:54:40 by yfan              #+#    #+#             */
/*   Updated: 2024/09/27 16:54:44 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
//# include <sys/ioctl.h>//！！！！！！ioctl function
# include "struct.h"
# include "define.h"

void    init_shell(t_shell *shell, char **env);
void    minishell_loop(t_shell *shell);
void    set_signal_handler(void);
void    handle_sigint(int sig);
void	set_prompt(t_shell *shell);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void    free_before_exit(t_shell *shell);
size_t	ft_strlen(const char *s);
void    configure_terminal(struct termios *termios_set);
char	**ft_split(char const *s, char c);
void    init_no_env(t_shell *shell);
t_env   *init_default_env(char **env);
t_env	*init_env_node(char *str);
void	free_char_array(char **array);
char	*get_env_content(char *full, char *var_name);
void	free_env(t_env *head);
//void    print_env(t_env *head);//print the list of env!!!
void	add_back_env_node(t_env	**head, t_env *new);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
void	update_env(t_shell *shell);
char	**env_list_to_char(t_env *env);
int	    get_env_list_size(t_env *head);
char	*get_full_env(t_env *env);
//void	ft_add_history(t_shell *shell);
//int	    is_only_space(char *str);
//int 	rep_prompt(char *prompt, char *prev_prompt);
int	    ft_strcmp(const char *s1, const char *s2);
char	*ft_strtrim(char const *s1, char const *set);
int	    lexer(t_shell *shell);
int 	is_empty_line_passed(t_shell *s);
int 	bad_pipe(t_shell *shell);
int 	syntax_error(char c);
int 	syntax_error_newline(void);
int     wrong_operator_check(const char *s);
char	*ft_strchr(const char *s, int c);
void	free_env_path(char **env, char *get_path);
void	ft_putstr_fd(char *s, int fd);
char    *expand_var(char *input, t_env *lst_env);
int     init_expansion(t_expansion *exp);
char	*ft_itoa(int n);
int     append_str(t_expansion *exp);
int     append_env(t_expansion *exp);
char    *expand_buffer(char *old_buffer, int *size);
size_t	ft_strlcpy(char *dst, const char *src, size_t siz);
char    *mini_get_env(const char *name, t_env *lst_env);
int		ft_isalnum(int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int     valid_exp(int c);
int		ft_isdigit(int c);
char    *expand_tilde(char *input, t_env *lst_env);

void    mini_execute(t_shell *shell, t_strcmd *str_cmd);
int     is_build_in(const char *s);
void	execute(char **cmd, char **env);
char	*get_path(char *cmd, char **env);
char	**env_split(char **env);
void    exec_cmd(t_strcmd *str_cmd, t_shell *shell);
void    red_out(t_strcmd *str_cmd, t_shell *shell);
void red_in(t_strcmd *str_cmd, t_shell *shell, char *here_doc);
void close_fds(int *fd, int num);

void child_signal_handler();
int     mini_builtin(int type, t_shell *shell, t_strcmd *cmd);
int     mini_exit(t_shell *shell, t_strcmd *cmd);
int     count_cmd(char **str);

extern int  g_status;


//-----------------------------------------------sw

# define ERR_PREF "minishell: "
# define TRUE 1
# define FALSE 0

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
//void	minishell_loop(void);
t_strcmd	*parse_line(char *line);
int		lexer_check(char *line);

char	*ft_strndup(const char *s, int n);
void	ft_putstr(char *s);
char	*ft_strncpy(char *dest, char *src, unsigned int n);

void    ft_err(char *s);
int		is_red(char *s); //is redirection

void	print_tab(char **s);
void	print_lst(t_list *lst);
void	print_lst_partition(t_list **partition);
void	print_token_str(t_strcmd *cmd_str);

void	print_token_struct(t_lstcmd *cmd_lst);
void	print_token_str(t_strcmd *cmd_str);

t_list	**partition_lst(t_list *lst_tk);
char	**lst_to_chatab(t_list *lst);
char	*lst_getstr(t_list *lst);

int		count_pipe(t_list *lst);
int		check_double_pipe(t_list *lst);
int		check_red_file(t_list *lst);
int		check_token_err(t_list *lst);

char *here_doc_name(void);
int has_heredoc(t_strcmd *str_cmd, t_shell *shell);
//-----------------------------------------------sw

#endif
