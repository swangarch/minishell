/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_labels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:46:33 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/08 12:46:35 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_red(char *s) //is redirection
{
	if (!strcmp(s, "<"))
		return (REDIN);
	if (!strcmp(s, "<<"))
		return (HEREDOC);
	if (!strcmp(s, ">"))
		return (REDOUT);
	if (!strcmp(s, ">>"))
		return (APPEND);
	return (TEXT);
}
