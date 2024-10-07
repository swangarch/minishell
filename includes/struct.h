/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:50:53 by yfan              #+#    #+#             */
/*   Updated: 2024/10/02 16:50:55 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_type
{
	WORD,
	HEREDOC,
	OUTPUT,
	APPEND,
	INPUT,
	UNKNOWN
}	t_type;

typedef struct s_token
{
	t_type			type;
	struct s_token	*next;
	struct s_token	*prev;
	char			*content;
}	t_token;

typedef struct s_cmd_tbl
{
	char				*cmd;
	t_token				*args;
	struct s_cmd_tbl	*next;
	int					index;
	t_token				*redirs;
	char				**cmd_args;
	char				*heredoc_name;
}	t_cmd_tbl;

typedef struct s_env
{
	struct s_env	*next;
	char			*content;
	char			*var_name;
}	t_env;

typedef struct s_shell
{
	int				print;
	char			**env;
	int				envless;
	char			*prompt;
	char			*heredoc;
	t_cmd_tbl		*cmd_tbls;
	t_env			*env_head;
	int				exit_code;
	int				std_fds[2];
	char			*user_name;
	int				color_codes;
	char			**cmd_paths;
	char			*prev_prompt;
	int				exec_on_pipe;
	int				should_expand;
	int				should_execute;
	int				expand_heredoc;
	struct termios	mirror_termios;
	char			*trimmed_prompt;
	char			*terminal_prompt;
	int				cmd_has_been_executed;
}	t_shell;

#endif
