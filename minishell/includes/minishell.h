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
# include "struct.h"
# include "define.h"

extern int	g_sig;

void		execute_commands(t_shell *shell);
void		minishell_loop(t_shell *shell);

/*builtin*/
int			mini_builtin(int type, t_shell *shell, int *p_fd, int i);
int			mini_pwd(char **cmd, t_env *head);
int			mini_exit(t_shell *shell, t_cmd **tab_cmd, int place, int *p_fd);
int			mini_env(char **env, t_cmd **tab_cmd, int place);
int			mini_unset(t_env **head, char **cmd);

int			is_build_in(const char *s);
int			count_cmd(char **str);
int			is_valid_name(const char *var);
int			is_valid_name_equal(const char *var);
int			mini_cd(t_env **head, char **cmd, char *home_path);
int			mini_echo(char **cmd);
int			mini_export(t_env **head, char **cmd);
void		set_pwd(t_env **lst_env, char *name, char *content);
void		unset_var(t_env **lst_env, const char *name);
void		set_var(t_env **lst_env, char **name, char *cmd);

/*execution*/
char		*get_path(char *cmd, t_shell *shell, int *p_fd);
char		**env_split(char **env);
int			init_pipe_fds(int **p_fd, int num_cmd, t_shell *shell);
void		set_child(int *num, int *p_fd, t_shell *shell, t_cmd *cmd);
void		final_execute(t_shell *shell, char *path, char **cmd, int *p_fd);
void		mini_execute(t_shell *shell, t_cmd **tab_cmd);
void		execute(char **cmd, t_shell *shell, int *p_fd);
void		close_multi_fd(int num, int *p_fd);

/*expansion*/
void		expand_tab(char **tab, t_env *env_head, int status);
void		expand_str_cmd(t_cmd **tab_cmd, t_env *env_head, int status);
char		*expand_var_here(char *input, t_env *lst_env, int status);
char		*expand_buffer(char *old_buffer, int *size);
int			append_str(t_expansion *exp);
int			append_env(t_expansion *exp);
int			init_expansion(t_expansion *exp);
int			valid_exp(int c);
int			handle_quotes(char *input, t_expansion *exp);
int			handle_exit_status(t_expansion *exp, int status);
int			handle_env_var(t_expansion *exp, t_env *lst_env);
int			handle_braces(char *input, t_expansion *exp, \
	t_env *lst_env, int status);
int			handle_variable(char *input, t_expansion *exp, t_env *lst_env);
int			handle_dollar(char *input, t_expansion *exp, \
	t_env *lst_env, int status);
int			handle_buffer(t_expansion *exp);
char		*expand_var(char *input, t_env *lst_env, int status);
char		*expand_tilde(char *input, t_env *lst_env);
int			expand_var_here_check(char *input, t_expansion *exp, \
	t_env *lst_env, int status);
void		rm_void_tab_cmd(t_cmd **tab_cmd);

/*initialization*/
t_env		*init_default_env(char **env);
t_env		*init_env_node(char *str);
char		*get_env_content(char *full, char *var_name);
void		add_back_env_node(t_env **head, t_env *new);
void		update_env(t_shell *shell);
char		**env_list_to_char(t_env *env);
size_t		get_env_list_size(t_env *head);
char		*get_full_env(t_env *env);
char		*mini_get_env(const char *name, t_env *lst_env);

void		init_no_env(t_shell *shell);
void		init_shell(t_shell *shell, char **env);

char		*ft_str4join(char *s1, char *s2, char *s3, char *s4);
char		*last_dir(char *s);
char		*join_prompt(void);

/*lexer*/
int			lexer(t_shell *shell);
int			is_empty_line_passed(t_shell *s);
int			bad_pipe(t_shell *shell);

int			wrong_operator_check(const char *input);

/*parsing*/
char		**lst_to_chatab(t_list *lst);
t_cmd		*cmd_from_lsts(t_list *cmd_lst, t_list *red);

void		on_lst_next_token_exist(t_list **curr, t_list **red, \
	t_list **cmd_lst);
t_cmd		*create_cmd(t_list *lst, t_list *cmd_lst, t_list *red);
t_cmd		**create_cmd_tab(char **tab);

void		lst_add_back_strn(char *line, t_list **lst_token, int *i, int j);
void		parse_word(char *line, t_list **lst_token, int *i);
t_list		*tokenize_line(char *line);
t_cmd		**parse_line(char *line);

int			is_red(char *s);
void		lst_add_back_str(char *s, t_list **lst_token);
void		parse_symbol_single(char *line, t_list **lst_token, int i);
void		parse_symbol_double(char *line, t_list **lst_token, int *i);
int			is_wordchar(char c);
char		**split_ign_quote(char const *s, char c);

int			count_pipe(t_list *lst);
int			red_next_err(char **tab);
int			parse_error(t_cmd **cmds);

int			get_tab_num(char **tab);
int			get_cmdtab_num(t_cmd **cmd_tab);
char		*lst_getstr(t_list *lst);
void		clear_lsts(t_list **lst, t_list **red, t_list **cmd_lst);
int			has_in(char **red);
int			has_out(char **red);

/*redirection*/
int			on_has_heredoc(t_cmd **tab_cmd, t_shell *shell, \
	char **here_docs, int index_p);
char		**process_heredocs(t_cmd **tab_cmd, t_shell *shell, int num_cmd);

char		*here_doc_name(int index_p);
int			has_heredoc(t_cmd *cmd, t_shell *shell);
void		delete_heredoc(char **here_docs);
void		close_fds(int *fd, int num);
int			last_redin(t_cmd *cmd, int i);

int			redir(t_cmd *cmd, t_shell *shell, int index_p);
int			red_out_tofile(t_cmd *cmd, int *fd_outfile, int *i);
int			red_out_append(t_cmd *cmd, int *fd_outfile, int *i);

/*utils*/
int			syntax_error(char c);
int			syntax_error_newline(void);
void		ft_put3str_fd(char *s1, char *s2, char *s3, int fd);
void		ft_err(char *s);

void		free_env(t_env *head);
void		free_env_path(char **env, char *get_path);
void		free_before_exit(t_shell *shell);
void		free_char_array(char **array);
void		free_in_loop(t_shell *shell);
void		free_2_char(char *s1, char *s2);
void		free_save_line(t_shell *shell, int *p_fd, char *path);
void		free_close(t_shell *shell, int *p_fd, int num);

void		configure_terminal(struct termios *termios_set);
void		handle_sigint(int sig);
int			event(void);
void		set_signal_handler(void);

void		ft_putstr(char *s);
char		*ft_strncpy(char *dest, char *src, unsigned int n);
char		*ft_strndup(const char *s, int n);
void		check_tty(t_shell *shell);

int			str_to_ll(const char *str, long long *val);
int			is_numeric(const char *str);
char		**split_by_equal(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
void		set_close(int *fds);

#endif
