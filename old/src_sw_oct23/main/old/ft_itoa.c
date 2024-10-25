/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:19:18 by yfan              #+#    #+#             */
/*   Updated: 2024/05/25 15:12:22 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_setchar(char *ptr, char c)
{
	int	idx;

	idx = 0;
	while (ptr[idx])
		idx++;
	ptr[idx++] = c;
	ptr[idx] = '\0';
	return (ptr);
}

static char	*ft_setnbr(char *ptr, int n)
{
	if (n == -2147483648)
	{
		ft_setnbr(ptr, n / 10);
		ft_setchar(ptr, -(n % 10) + '0');
	}
	else if (n < 0)
	{
		ft_setchar(ptr, '-');
		ft_setnbr(ptr, -n);
	}
	else
	{
		if (n > 9)
			ft_setnbr(ptr, n / 10);
		ft_setchar(ptr, n % 10 + '0');
	}
	return (ptr);
}

static int	ft_cnt_itoa(int n)
{
	int	cnt;

	cnt = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -(n / 10);
		cnt += 2;
	}
	while (n)
	{
		cnt++;
		n /= 10;
	}
	return (cnt);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		cnt;

	cnt = ft_cnt_itoa(n);
	ptr = (char *)malloc((cnt + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	*ptr = '\0';
	if (!ft_setnbr(ptr, n))
		return (NULL);
	return (ptr);
}
