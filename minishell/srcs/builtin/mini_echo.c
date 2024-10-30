/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:24:53 by yfan              #+#    #+#             */
/*   Updated: 2024/10/28 17:39:25 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	echo_check_newline(char **cmd, int *info)
{
	while (cmd[info[2]])
	{
		if (!strncmp(cmd[info[2]], "-n", 2))
		{
			info[1] = TRUE;
			info[3] = 2;
			while (cmd[info[2]][info[3]])
			{
				if (cmd[info[2]][info[3]] != 'n')
				{
					info[1] = FALSE;
					break ;
				}
				++info[3];
			}
			if (info[1])
			{
				info[0] = TRUE;
				++info[2];
				continue ;
			}
		}
		break ;
	}
}

int	mini_echo(char **cmd)
{
	int	info[4];

	info[0] = FALSE;
	info[2] = 1;
	echo_check_newline(cmd, info);
	while (cmd[info[2]])
	{
		ft_putstr_fd(cmd[info[2]], STDOUT_FILENO);
		if (cmd[info[2] + 1])
		{
			ft_putstr_fd(" ", STDOUT_FILENO);
		}
		++info[2];
	}
	if (!info[0])
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
