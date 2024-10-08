/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:46:56 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/02 16:46:57 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*get_username()
{
	return (getenv("USER"));
}

char	*ft_str3join(char *s1, char *s2, char *s3)
{
	char	*temp1;
	char	*result;

	temp1 = ft_strjoin(s1, s2);//protect
	result = ft_strjoin(temp1, s3);
	free(temp1);
	return (result);
}

char	*ft_str4join(char *s1, char *s2, char *s3, char *s4)
{
	char	*temp1;
	char	*temp2;
	char	*result;

	temp1 = ft_strjoin(s1, s2);//protect
	temp2 = ft_strjoin(temp1, s3);
	free(temp1);
	result = ft_strjoin(temp2, s4);
	free(temp2);
	return (result);
}

char	*join_prompt(void)//(char *s1, char *s2, char *s3)
{
	char	cwd[PATH_MAX];
	char	*read_pwd;
	char	*current_path = NULL;
	char	*join_path = NULL;

	read_pwd = getcwd(cwd, PATH_MAX);
	if (!read_pwd)
	{
		perror("getcwd() error");
		current_path = ft_strdup("$ ");//protect
	}
	else
	{
		current_path = ft_strjoin(ft_strdup(cwd),"$ ");//protect
	}
	
	join_path = ft_str4join(BLUE_B "yf&sw" COLOR_END, WHITE_B "@" COLOR_END, RED_B "minishell❄ " COLOR_END, current_path);
	free(current_path);
	return (join_path);
	//return (ft_strjoin(text_color("yf&sw", 31), text_color("minishell❀", 33)));
	//return (ft_strjoin("yf&sw", "minishell:"));
}
