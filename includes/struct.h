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

typedef struct s_cmd
{
	char	**red;
	char	**cmd;
	int		has_in;
	int		has_out;
}	t_cmd;

typedef struct s_env
{
	struct s_env	*next;
	char			*content;
	char			*var_name;
}	t_env;

typedef struct s_shell
{
	char			*prompt;
	char			*home_path;
	char			**here_docs;
	t_env			*env_head;
	char			**env;
	int				std_fds[2];
	int				status;
	char			*trimmed_prompt;
	char			*terminal_prompt;
	t_cmd			**tab_cmd;
	pid_t			pid;
	struct termios	termios_set;
}	t_shell;

typedef struct s_expansion
{
	int		size;
	char	*result;
	int		len;
	int		i;
	int		k;
	int		in_squote;
	int		in_dquote;
	char	*exit_status;
	char	var_name[256];
	char	*env_val;
}	t_expansion;

typedef struct s_lstcmd
{
	t_list	*full_cmd;
	t_list	*redin;
	t_list	*redout;
}	t_lstcmd;

typedef struct s_split
{
	int	i;
	int	j;
	int	c;
	int	ins;
	int	ind;
}	t_split;

#endif
