/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:44:00 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/08 12:44:01 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

static	int	slen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strndup(const char *s, int n)
{
	char	*dup;
	int		i;
	int		len;
	int		s_len;

	i = 0;
	if (!s)
		return (NULL);
	s_len = slen(s);
	if (n < s_len)
		len = n;
	else
		len = s_len;
	dup = malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	while (s[i] && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	check_tty(t_shell *shell)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		shell->trimmed_prompt = ft_strtrim(line, SPACES);
		execute_commands(shell);
		free(line);
		free(shell->trimmed_prompt);
		shell->trimmed_prompt = NULL;
		line = get_next_line(STDIN_FILENO);
	}
}
