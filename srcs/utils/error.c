/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:10:23 by yfan              #+#    #+#             */
/*   Updated: 2024/10/29 15:10:26 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	syntax_error(char c)
{
	ft_putstr_fd(SHELL SYN_ERR " `", STDERR_FILENO);
	write(STDERR_FILENO, &c, 1);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (TRUE);
}

int	syntax_error_newline(void)
{
	ft_putstr_fd(SHELL SYN_ERR_NEWLINE "\n", STDERR_FILENO);
	return (TRUE);
}

void	ft_put3str_fd(char *s1, char *s2, char *s3, int fd)
{
	if (s1)
		ft_putstr_fd(s1, fd);
	if (s2)
		ft_putstr_fd(s2, fd);
	if (s3)
		ft_putstr_fd(s3, fd);
}

void	ft_err(char *s)
{
	ft_putstr_fd(s, 2);
}
