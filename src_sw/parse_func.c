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

void	print_tab(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putstr(s[i]);
		write(1, "$", 1);
		write(1, "\n", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	print_lst(t_list *lst)
{
	t_list *curr;

	curr = lst;
	while (curr)
	{
		ft_putstr((char *)(curr->content));
		//write(1, "$", 1);
		if (curr->next)
			write(1, "___", 3);
		curr = curr->next;
	}
	write(1, "$", 1);
	write(1, "\n", 1);
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
				if (line[i + j] == ' ' || line[i + j] == '>' || line[i + j] == '<' || line[i + j] == '|')//|| line[i + j] == '\"' || line[i + j] == '\'')
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
		// else if (line[i] != ' ' && !line[i + 1])
		// {
		// 	token = ft_strndup(&line[i], 1);//protect
		// 	ft_lstadd_back(&lst_token, ft_lstnew(token));//protect
		// 	i++;
		// }
		else if (line[i] == ' ')
		{
			i++;
			continue;
		}
		i++;
	}
	//print_lst(lst_token);
	return (lst_token);
}

int		check_double_pipe(t_list *lst)///check if pipe is in the end
{
	t_list	*curr;
	int		has_double_pipe;

	has_double_pipe = 0;  //protect content
	curr = lst;
	while (curr)
	{
		if (!ft_strcmp((char*)(curr->content), "|") && curr->next && !ft_strcmp((char*)(curr->next->content), "|"))
		{
			ft_err(ERR_PREF "syntax error near unexpected token `|'\n");
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}
/*
int		check_last_is_pipe(t_list *lst)///check if pipe is in the end
{
	t_list	*curr;

	curr = lst;
	if(!curr)
		return (1);
	while (curr->next)
		curr = curr->next;
	if (!ft_strcmp((char*)(curr->content), "|"))
	{
		ft_err(ERR_PREF "syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}*/

int		count_pipe(t_list *lst)
{
	t_list	*curr;
	int		num_pipe;

	num_pipe = 0;
	curr = lst;
	while (curr)
	{
		if (!ft_strcmp((char*)(curr->content), "|")) 
			num_pipe++;
		curr = curr->next;
	}
	return (num_pipe);
}

// t_list	**partition_lst(t_list *lst_tk)
// {
// 	t_list	**partition;
// 	t_list	*part_head;
// 	t_list	*curr_quick;
// 	t_list	*curr_slow;

// 	int		i = 0;
// 	partition = (t_list **)malloc(sizeof(t_list *) * (count_pipe(lst_tk) + 2));
// 	if (!partition)
// 		return (NULL);//protect
// 	curr_quick = lst_tk;
// 	curr_slow = lst_tk;
// 	part_head = lst_tk;
// 	partition[i] = part_head;
// 	while (curr_quick)
// 	{
// 		curr_slow = curr_quick;
// 		curr_quick = curr_quick->next;
// 		if (curr_quick && !ft_strcmp((char*)(curr_quick->content), "|"))
// 		{
// 			curr_slow->next = NULL;
// 			if(curr_quick->next)
// 			{
// 				curr_quick = curr_quick->next;
// 				part_head = curr_quick;
// 				i++;
// 				partition[i] = part_head;
// 			}
// 		}
// 	}
// 	i++;
// 	partition[i] = NULL;
//  	return (partition);
// }

t_list	**partition_lst(t_list *lst_tk)
{
	t_list	**partition;
	t_list	*curr_quick;
	t_list	*curr_slow;

	int		i = 0;
	partition = (t_list **)malloc(sizeof(t_list *) * (count_pipe(lst_tk) + 2));
	if (!partition)
		return (NULL);//protect
	curr_quick = lst_tk;
	//curr_slow = lst_tk;
	partition[i] = curr_quick;
	while (curr_quick)
	{
		curr_slow = curr_quick;
		curr_quick = curr_quick->next;
		if (curr_quick && !ft_strcmp((char*)(curr_quick->content), "|"))
		{
			curr_slow->next = NULL;
			if(curr_quick->next)
			{
				curr_quick = curr_quick->next;
				i++;
				partition[i] = curr_quick;
			}
		}
	}
	i++;
	partition[i] = NULL;
 	return (partition);
}

void	print_lst_partition(t_list **partition)
{
	int	i = 0;

	if (!partition)
		return ;
	while(partition[i])
	{
		print_lst(partition[i]);
		i++;
	}
}

char	**lst_to_chatab(t_list *lst)//////////////NO
{
	int	size;
	int	i; 
	t_list *curr;
	char **chatab;

	size = ft_lstsize(lst);
	i = 0;
	curr = lst;
	chatab = malloc(sizeof(char *) * (size + 1));
	if (!chatab)
		return (NULL);
	while (i < size)
	{
		chatab[i] = (char *)(curr->content);
		curr = curr->next;
		i++;
	}
	chatab[i] = NULL;
	return (chatab);
}

typedef struct	s_cmd
{
	char *cmd;
	char **full_cmd;
	t_list *redin;
	t_list *redout;
}	t_cmd;

#define REDIN 0
#define HEREDOC 1
#define REDOUT 2
#define APPEND 3
#define TEXT -1

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

char	*lst_getstr(t_list *lst)
{
	return ((char *)lst->content);
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