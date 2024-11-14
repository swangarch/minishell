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

/**
 * @brief Checks for the "-n" option in echo command
 *
 * This function inspects the command arguments for the "-n" option,
 * which indicates that the output should not be followed by a newline.
 * It updates the info array to reflect whether the "-n" option is
 * present and how many 'n' characters follow it.
 *
 * @param cmd Array of command-line arguments
 * @param info Array containing flags and index information
 */
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

char	*ft_join_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

/**
 * @brief Outputs the arguments for the echo command
 *
 * This function prints the command-line arguments to standard output.
 * It checks for the "-n" option to determine if a newline should be
 * appended at the end of the output. The arguments are separated by spaces.
 *
 * @param cmd Array of command-line arguments
 * @return Returns 0 upon completion
 */
int	mini_echo(char **cmd)
{
	int		info[4];
	char	*result;

	info[0] = FALSE;
	info[2] = 1;
	result = NULL;
	echo_check_newline(cmd, info);
	while (cmd[info[2]])
	{
		result = ft_join_free(result, cmd[info[2]]);
		if (cmd[info[2] + 1])
		{
			result = ft_join_free(result, " ");
		}
		++info[2];
	}
	if (!info[0])
		result = ft_join_free(result, "\n");
	if (result)
		ft_putstr_fd(result, STDOUT_FILENO);
	free(result);
	return (0);
}
