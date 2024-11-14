/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:23:12 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/30 15:52:00 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	c_len(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	if (start >= i)
		return (0);
	else if (start + len > i)
		return (i - start);
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	i = 0;
	j = 0;
	str = (char *)malloc((c_len(s, start, len) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	while (s[i])
	{
		if (i == start)
		{
			while (j < len && s[i + j])
			{
				str[j] = s[i + j];
				j++;
			}
			break ;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}
/*
#include <stdio.h>
int	main(void)
{	
	printf("%s\n", "Hello world my friend, how are you");
	printf("%s\n", ft_substr("Hello world my friend, how are you", 6, 50));
	printf("%s\n", ft_substr("tripouille", 1, 1));
	printf("%s\n", ft_substr("1", 42, 42000000));
	return (0);
}*/								
