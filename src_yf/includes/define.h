/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:54:14 by yfan              #+#    #+#             */
/*   Updated: 2024/09/27 16:57:25 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/* colors */
// # define RED "\001\033[1;31m\002"
// # define GREEN "\001\033[1;32m\002"
// # define YELLOW "\001\033[1;33m\002"
// # define BLUE "\001\033[1;34m\002"
// # define COLOR_E "\001\033[0m\002"

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

# define PATH_MAX 4096

# define TRUE 1
# define FALSE 0

# define MES_ARG_NO_ONE "Usage: ./minishell [no argument]\n"
# define MES_PATH_ERR "Path got failed!\n"
# define MES_CUR_PATH_ERR "Current path got failed!\n"
# define MES_MALLOC_ERR "Malloc failed!\n"
# define MES_CREAT_NODE "Creat node failed!\n"
# define MES_SQUOTE_ERR "Syntax error: unclosed single quote\n"
# define MES_DQUOTE_ERR "Syntax error: unclosed double quote\n"
# define MES_DUP_ERR "Dup failed!\n"
# define MES_EXIT_OP "exit: options are not allowed\n"
# define MES_EXIT_NUM ": numeric argument required\n"
# define MES_EXIT_TOO_MANY "exit: too many arguments\n"
# define MES_ENV_ERR "env: options or arguments are not allowed\n"
# define MES_ENSET_ERR "unset [no options]!\n"
# define MES_ENSET_OP "unset: options are not allowed\n"
# define MES_EXPORT_OP "export: options are not allowed\n"
# define MES_PWD_OP "pwd: options are not allowed\n"
# define EXPORT_PRE "declare -x "
# define MES_EXPORT_ERR "export: not an identifier: "
# define MES_CD_TOO_MANY "cd: too many arguments\n"
# define MES_CD_HOME "minishell: cd: HOME not set\n"
# define MES_CD_OLD "minishell: cd: OLDPWD not set\n"
# define MES_CD_ENOENT ": No such file or directory\n"
# define MES_CD_ENOTDIR ": Not a directory\n"
# define MES_CD_EACCES ": Permission denied\n"

# define SPACES " \n\t\r\f\v"
# define OPERATOR "|><"
# define SHELL "minihsell: "
# define ISDIR "Is a directory"
# define DQUOTE '\"'
# define SQUOTE '\''
# define CMD_NOT_FND "command '' not found"
# define SYN_ERR "syntax error near unexpected token"
# define SYN_ERR_NEWLINE "syntax error near unexpected token `newline'"

# define INIT_SIZE 64
# define FACTOR 2
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# define NOBULTIN 0
# define MINI_ECHO 1
# define MINI_CD 2
# define MINI_PWD 3
# define MINI_EXPORT 4
# define MINI_UNSET 5
# define MINI_ENV 6
# define MINI_EXIT 7

#endif
