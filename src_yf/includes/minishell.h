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
# include <sys/stat.h>
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
void    free_before_exit(t_shell *shell);
void    configure_terminal(struct termios *termios_set);
void    init_no_env(t_shell *shell);
t_env   *init_default_env(char **env);
t_env	*init_env_node(char *str);
void	free_char_array(char **array);
char	*get_env_content(char *full, char *var_name);
void	free_env(t_env *head);
//void    print_env(t_env *head);//print the list of env!!!
void	add_back_env_node(t_env	**head, t_env *new);
void	update_env(t_shell *shell);
char	**env_list_to_char(t_env *env);
int	    get_env_list_size(t_env *head);
char	*get_full_env(t_env *env);
//void	ft_add_history(t_shell *shell);
//int	    is_only_space(char *str);
//int 	rep_prompt(char *prompt, char *prev_prompt);
int	    ft_strcmp(const char *s1, const char *s2);
int	    lexer(t_shell *shell);
int 	is_empty_line_passed(t_shell *s);
int 	bad_pipe(t_shell *shell);
int 	syntax_error(char c);
int 	syntax_error_newline(void);
int     wrong_operator_check(const char *s);
void	free_env_path(char **env, char *get_path);
char    *expand_var(char *input, t_env *lst_env, int status);
int     init_expansion(t_expansion *exp);
int     append_str(t_expansion *exp);
int     append_env(t_expansion *exp);
char    *expand_buffer(char *old_buffer, int *size);
char    *mini_get_env(const char *name, t_env *lst_env);
int     valid_exp(int c);
char    *expand_tilde(char *input, t_env *lst_env);

void    mini_execute(t_shell *shell, t_cmd **tab_cmd);
int     is_build_in(const char *s);
void	execute(char **cmd, char **env);
char	*get_path(char *cmd, char **env);
char	**env_split(char **env);
int    red_out(t_cmd *tab_cmd, t_shell *shell);
int    red_in(t_cmd *tab_cmd, t_shell *shell, int index_p);
void close_fds(int *fd, int num);

void child_signal_handler();
int     mini_builtin(int type, t_shell *shell, t_cmd **tab_cmd, int i);
int     mini_exit(t_shell *shell, t_cmd **tab_cmd, int place);
int     count_cmd(char **str);
int     mini_env(char **env, t_cmd **tab_cmd, int place);
int     mini_unset(t_env **head, char **cmd);
int     str_to_ll(const char *str, long long *val);
int     is_numeric(const char *str);
int is_valid_name(const char *var);
void	unset_var(t_env **lst_env, const char *name);
int     mini_export(t_env **head, char **cmd);
void	set_var(t_env **lst_env, char **name, char *cmd);
char    **split_by_equal(const char *s);
int     mini_echo(char **cmd);
int     mini_pwd(char **cmd);
int     mini_cd(t_env **head, char **cmd);
void	set_pwd(t_env **lst_env, char *name, char *content);

char    *expand_var_here(char *input, t_env *lst_env, int status);

void	free_in_loop(t_shell *shell);

//char    *cd_set_dir(t_env **head, char **cmd);
//int     cd_change_dir(char *dir);
void    ft_put3str_fd(char *s1, char *s2, char *s3, int fd);
//int		set_pwd_begin(t_env **lst_env, char *full);
//void	set_pwd_end(t_env **lst_env, t_env *current, char *full);

//void heredoc_sig_handle(int sig);
void handle_sigquit(int sig);

void	free_2_char(char *s1, char *s2);
//int     export_set_var(t_env **head, char **cmd, int i, int *inval);
//void    export_print(t_env *current);
//void    echo_check_newline(char **cmd, int *info);
//int		set_var_begin(t_env **lst_env, char *cmd);
int     handle_quotes(char *input, t_expansion *exp);
int     handle_dollar(char *input, t_expansion *exp, t_env *lst_env, int status);
int     handle_exit_status(t_expansion *exp, int status);
int     handle_braces(char *input, t_expansion *exp, t_env *lst_env, int status);
int     handle_env_var(t_expansion *exp, t_env *lst_env);
int     handle_variable(char *input, t_expansion *exp, t_env *lst_env);
int     handle_buffer(t_expansion *exp);
int  init_pipe_fds(int **p_fd, int num_cmd, t_shell *shell);
void    set_child(int *num, int *p_fd, t_shell *shell, t_cmd *cmd);

extern int  g_sigint_flag;


//-----------------------------------------------sw

# define ERR_PREF "minishell: "
# define TRUE 1
# define FALSE 0

#define REDIN 1
#define HEREDOC 2
#define REDOUT 3
#define APPEND 4
#define TEXT 0


char	*ft_str4join(char *s1, char *s2, char *s3, char *s4);
char	*join_prompt(void);
t_cmd	**parse_line(char *line);
int		lexer_check(char *line);

char	*ft_strndup(const char *s, int n);
void	ft_putstr(char *s);
char	*ft_strncpy(char *dest, char *src, unsigned int n);

void    ft_err(char *s);
int		is_red(char *s); //is redirection

void	print_tab(char **s);
void	print_lst(t_list *lst);
void	print_lst_partition(t_list **partition);

void	print_token_struct(t_lstcmd *cmd_lst);

t_list	**partition_lst(t_list *lst_tk);
char	**lst_to_chatab(t_list *lst);
char	*lst_getstr(t_list *lst);

int		count_pipe(t_list *lst);
int		check_double_pipe(t_list *lst);
int		check_red_file(t_list *lst);
int		check_token_err(t_list *lst);

char *here_doc_name(int index_p);
int has_heredoc(t_cmd *cmd, t_shell *shell);
char **process_heredocs(t_cmd **tab_cmd, t_shell *shell, int num_cmd);
void delete_heredoc(char **here_docs);

int	get_cmdtab_num(t_cmd **cmd_tab);
int	get_tab_num(char **tab);

int		is_wordchar(char c);
void	parse_symbol_single(char *line, t_list	**lst_token, int i);
void	parse_symbol_double(char *line, t_list	**lst_token, int *i);

int	parse_error(t_cmd **cmds);

t_cmd *create_cmd(t_list *lst, t_list *cmd_lst, t_list *redin, t_list *redout);
t_cmd	**create_cmd_tab(char **tab);
t_list	*tokenize_line(char *line);
void on_lst_next_token_exist(t_list **curr, t_list **redin, t_list **redout, t_list **cmd_lst);
t_cmd *cmd_from_lsts(t_list *cmd_lst, t_list *redin, t_list *redout);
void clear_lsts(t_list **lst, t_list **redin, t_list **redout, t_list **cmd_lst);
void do_noting(void *arg);
char	**split_ign_quote(char const *s, char c);
//-----------------------------------------------sw

#endif
