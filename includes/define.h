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
# define RED "\001\033[1;31m\002"
# define GREEN "\001\033[1;32m\002"
# define YELLOW "\001\033[1;33m\002"
# define BLUE "\001\033[1;34m\002"
# define COLOR_E "\001\033[0m\002"

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

#endif
