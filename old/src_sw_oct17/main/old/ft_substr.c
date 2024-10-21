/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:27:59 by yfan              #+#    #+#             */
/*   Updated: 2024/05/24 18:06:23 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	idx;
	size_t	size;
	char	*ptr;

	if (!s)
		return (0);
	size = len;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		size = ft_strlen(s + start);
	ptr = (char *)malloc((size + 1) * sizeof(char));
	if (!ptr)
		return (0);
	idx = 0;
	while (s[start + idx] && idx < len)
	{
		ptr[idx] = s[start + idx];
		idx++;
	}
	ptr[idx] = '\0';
	return (ptr);
}
