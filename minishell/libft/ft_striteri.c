/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:41:08 by shuwang           #+#    #+#             */
/*   Updated: 2024/05/27 18:23:51 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
#include <stdio.h>
void	to_up(unsigned int i, char* s)
{
	if (i % 2 == 0 && (s[i] >= 'a' && s[i] <= 'z'))
		s[i] = s[i] - 32;
}

int	main(void)
{
	char	s[] = "hello world how are you";
	ft_striteri(s, &to_up);
	//ft_striteri(s, &splusi);
	printf("%s\n", s);
	return (0);
}*/	
