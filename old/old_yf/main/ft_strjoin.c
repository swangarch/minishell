/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:42:11 by yfan              #+#    #+#             */
/*   Updated: 2024/05/22 13:49:49 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	idx;
	size_t	idx_join;
	size_t	len;
	char	*ptr;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = (char *)malloc(len * sizeof(char));
	if (!ptr)
		return (0);
	idx = 0;
	idx_join = 0;
	while (s1[idx])
		ptr[idx_join++] = s1[idx++];
	idx = 0;
	while (s2[idx])
		ptr[idx_join++] = s2[idx++];
	ptr[idx_join] = '\0';
	return (ptr);
}
