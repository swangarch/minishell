/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:53:53 by yfan              #+#    #+#             */
/*   Updated: 2024/10/28 18:53:55 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int  init_pipe_fds(int **p_fd, int num_cmd, t_shell *shell)
{
    int i;
    *p_fd = malloc(2 * (num_cmd - 1) * sizeof(int));
    if (!*p_fd)
    {
        shell->status = 1;
        return (1);
    }
    i = 0;
    while (i < num_cmd - 1)
    {
        if (pipe(*p_fd + i * 2) == -1)
        {
            shell->status = 2;
            perror(SHELL "pipe");
            free(*p_fd);
            return (1);
        }
        ++i;
    }
    return (0);
}

void    set_child(int *num, int *p_fd, t_shell *shell, t_cmd *cmd)
{
    int i;
    if (num[1] > 0)
    {
        if (dup2(p_fd[(num[1] - 1) * 2], 0) == -1)
        {
            perror(SHELL "dup2");
            exit(EXIT_FAILURE);
        }
    }
    if (num[1] < num[0] - 1)
    {
        if (dup2(p_fd[num[1] * 2 + 1], 1) == -1)
        {
            perror(SHELL "dup2");
            exit(EXIT_FAILURE);
        }
    }
    if (!red_in(cmd, shell, num[1]) || !red_out(cmd, shell))
    {
        free_before_exit(shell);
        free(p_fd);
        exit(EXIT_FAILURE);
    }
    i = 0;
    while (i < 2 * (num[0] - 1))
        close(p_fd[i++]);
}
