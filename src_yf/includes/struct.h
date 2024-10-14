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
	char			*prompt;
	char			*heredoc;
	t_cmd_tbl		*cmd_tbls;
	t_env			*env_head;
	char			**env;
	int				std_fds[2];
	char			*trimmed_prompt;
	char			*terminal_prompt;
}	t_shell;

typedef struct s_expansion
{
	int				size;
	char			*result;
	int				len;
	int				i;
	int				k;
	int				in_squote;
	int				in_dquote;
	char			*exit_status;
	char			var_name[256];
	char			*env_val;
}	t_expansion;

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
	int	 num_cmd;
}	t_strcmd;

#endif
