/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:54:29 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/02 16:54:30 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	parse_symbol(char *line, t_list	*lst_token, char *token, int *i)
{

}

t_list	*split_line(char *line)
{
	int		i;
	int		j;
	t_list	*lst_token;
	char *token;

	if (!line)
		return (NULL);
	lst_token = NULL;
	i = 0;
	if (!ft_strlen(line))
		return (NULL);
	while (line[i])
	{
		if (!ft_strncmp(line + i, ">>", 2))
		{
			token = ft_strdup(">>");//protect
			ft_lstadd_back(&lst_token, ft_lstnew(token));//protect
			i = i + 1;
		}
		else if (!ft_strncmp(line + i, "<<", 2))
		{
			token = ft_strdup("<<");//protect
			ft_lstadd_back(&lst_token, ft_lstnew(token));//protect
			i = i + 1;
		}
		else if (line[i] == '>')
		{
			token = ft_strdup(">");//protect
			ft_lstadd_back(&lst_token, ft_lstnew(token));//protect
		}
		else if (line[i] == '<')
		{
			token = ft_strdup("<");//protect
			ft_lstadd_back(&lst_token, ft_lstnew(token));//protect
		}
		else if (line[i] == '|')
		{
			token = ft_strdup("|");//protect
			ft_lstadd_back(&lst_token, ft_lstnew(token));//protect
		}
		else if (line[i] == '\'')
		{
			j = 1;
			while (line[i + j])
			{
				if (line[i + j] == '\'')
				{
					token = ft_strndup(&line[i], j + 1);
					ft_lstadd_back(&lst_token, ft_lstnew(token));//protect
					i = i + j;
					break ;
				}
				j++;
			}
		}
		else if (line[i] == '\"')
		{
			j = 1;
			while (line[i + j])
			{
				if (line[i + j] == '\"')
				{
					token = ft_strndup(&line[i], j + 1);
					ft_lstadd_back(&lst_token, ft_lstnew(token));//protect
					i = i + j;
					break ;
				}
				j++;
			}
		}
		else if (line[i] != ' ')// && line[i + 1])
		{
			j = 0;
			while (line[i + j])
			{
				if (line[i + j] == '\"')
				{
					j++;
					while (line[i + j])
					{
						if (line[i + j] == '\"')
						{
							j++;
							break ;
						}
						j++;
					}
				}
				else if (line[i + j] == ' ' || line[i + j] == '>' || line[i + j] == '<' || line[i + j] == '|')
				{
					token = ft_strndup(&line[i], j);
					ft_lstadd_back(&lst_token, ft_lstnew(token));//protect
					i = i + j - 1;
					break;
				}
				else if (i + j == (int)ft_strlen(line) - 1)
				{
					token = ft_strndup(&line[i], j + 1);//protect
					ft_lstadd_back(&lst_token, ft_lstnew(token));//protect
					i = i + j;
					break;
				}
				j++;
			}
		}
		else if (line[i] == ' ')
		{
			i++;
			continue;
		}
		i++;
	}
	return (lst_token);
}

// t_cmd	*cmd_token(t_list *cmd_lst)
// {
// 	t_list	*full_cmd;
// 	t_list	*redin;
// 	t_list	*redout;
// 	t_cmd	*cmd_struct = malloc(sizeof(t_cmd));
// 	if (!cmd_struct)
// 		return (NULL);
// 	t_list	*curr;

// 	curr = cmd_lst;
// 	redin = NULL;
// 	redout = NULL;
// 	while (curr)
// 	{
// 		if (curr->next)
// 		{
// 			if (is_red(lst_getstr(curr)) == REDIN || is_red(lst_getstr(curr) == HEREDOC))
// 			{
// 				ft_lstadd_back(&redin, ft_lstnew(curr->content));
// 				curr = curr->next;
// 				ft_lstadd_back(&redin, ft_lstnew(curr->content));
// 			}
// 			if (is_red(lst_getstr(curr) == REDOUT || is_red(lst_getstr(curr)) == APPEND))
// 			{
// 				ft_lstadd_back(&redout, ft_lstnew(curr->content));
// 				curr = curr->next;
// 				ft_lstadd_back(&redout, ft_lstnew(curr->content));
// 			}
// 		}
// 		curr = curr->next;
// 	}
// 	return (cmd_struct);
// }

// t_cmd	*cmd_token(t_list *cmd_lst)
// {
// 	t_list	*full_cmd;
// 	t_list	*redin;
// 	t_list	*redout;
// 	if (!cmd_lst)
// 		return (NULL);
// 	t_cmd	*cmd_struct = malloc(sizeof(t_cmd));
// 	if (!cmd_struct)
// 		return (NULL);
// 	t_list	*curr_quick;
// 	t_list	*curr_slow;

// 	curr_quick = cmd_lst;
// 	curr_slow = curr_quick;
// 	redin = NULL;
// 	redout = NULL;
// 	while (curr_quick->next)
// 	{
// 		curr_quick = curr_quick->next;
		
// 		if (curr_quick->next)
// 		{
// 			if (is_red(lst_getstr(curr_quick)) == REDIN || is_red(lst_getstr(curr_quick) == HEREDOC))
// 			{
// 				ft_lstadd_back(&redin, ft_lstnew(curr_quick->content));
// 				curr_quick = curr_quick->next;
// 				ft_lstadd_back(&redin, ft_lstnew(curr_quick->content));
// 				curr_quick = curr_quick->next;
// 				curr_slow->next = curr_quick;
// 				curr_slow = curr_slow->next;
// 			}
// 			else if (is_red(lst_getstr(curr_quick) == REDOUT || is_red(lst_getstr(curr_quick)) == APPEND))
// 			{
// 				ft_lstadd_back(&redout, ft_lstnew(curr_quick->content));
// 				curr_quick = curr_quick->next;
// 				ft_lstadd_back(&redout, ft_lstnew(curr_quick->content));
// 				curr_quick = curr_quick->next;
// 				curr_slow->next = curr_quick;
// 				curr_slow = curr_slow->next;//////////////////////////////
// 			}
// 		}
// 		else
// 			curr_slow = curr_slow->next;
// 	}
// 	return (cmd_struct);
// }

void	parse_line(char *line)
{	
	char	*trimmed_line;
	t_list	*lst_tk;
	t_list	**partition;
	int		num_pipe;

	trimmed_line = ft_strtrim(line, " ");
	lst_tk = split_line(trimmed_line);

	num_pipe = count_pipe(lst_tk);
	//print_lst(lst_tk);
	check_double_pipe(lst_tk);
	//check_last_is_pipe(lst_tk);

	//printf("The number of pipe is %d\n", num_pipe);
	partition = partition_lst(lst_tk);
	print_lst_partition(partition);

	/*
	write(1, "\n", 1);
	int	i = 0;
	while (partition[i])
	{
		print_tab(lst_to_chatab(partition[i]));
		i++;
	}*/
	return;
}