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

void	parse_symbol_single(char *line, t_list	**lst_token, int i)
{
	char *token;

	token = NULL;
	if (line[i] == '>')
	{
		token = ft_strdup(">");//protect
		ft_lstadd_back(lst_token, ft_lstnew(token));//protect
	}
	if (line[i] == '<')
	{
		token = ft_strdup("<");//protect
		ft_lstadd_back(lst_token, ft_lstnew(token));//protect
	}
	if (line[i] == '|')
	{
		token = ft_strdup("|");//protect
		ft_lstadd_back(lst_token, ft_lstnew(token));//protect
	}
}

void	parse_symbol_double(char *line, t_list	**lst_token, int *i)
{
	char *token;

	token = NULL;
	if(!ft_strncmp(line + *i, ">>", 2))
		token = ft_strdup(">>");
	else if (!ft_strncmp(line + *i, "<<", 2))
		token = ft_strdup("<<");//protect
	ft_lstadd_back(lst_token, ft_lstnew(token));//protect
	(*i)++;
}

int		is_wordchar(char c)
{
	if (c == '\0')
		return (0);
	if (c == ' ' || c == '>' || c == '<' || c == '|')
		return (0);
	return (1);
}

void	test(void)
{
	
}

void	parse_word(char *line, t_list **lst_token, int *i)
{
	int		in_squote;
	int		in_dquote;
	int		j;
	char	*token;

	in_squote = 0;
	in_dquote = 0;
	j = 0;
	while (line[*i + j])
	{
		if (line[*i + j] == '\'' && !in_dquote)
			in_squote = !in_squote;
		if (line[*i + j] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		if (!is_wordchar(line[*i + j]) && !in_squote && !in_dquote)
		{
			token = ft_strndup(&line[*i], j);//protect
			ft_lstadd_back(lst_token, ft_lstnew(token));//protect
			*i = *i + j - 1;
			return ;
		}
		else if (*i + j == (int)ft_strlen(line) - 1)
		{
			token = ft_strndup(&line[*i], j + 1);//protect
			ft_lstadd_back(lst_token, ft_lstnew(token));//protect
			*i = *i + j;
			return ;
		}
		j++;
	}
}

t_list	*split_line(char *line)
{
	int		i;
	t_list	*lst_token;

	if (!line)
		return (NULL);
	lst_token = NULL;
	i = 0;
	if (!ft_strlen(line))
		return (NULL);
	while (line[i])
	{
		if (!ft_strncmp(&line[i], ">>", 2) || !ft_strncmp(&line[i], "<<", 2))
			parse_symbol_double(line, &lst_token, &i);
		else if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			parse_symbol_single(line, &lst_token, i);
		else if (is_wordchar(line[i]))
			parse_word(line, &lst_token, &i);
		i++;
	}
	return (lst_token);
}

//check error

t_lstcmd	*tokenize_cmd(t_list *cmd_lst)
{
	t_list	*full_cmd;
	t_list	*redin;
	t_list	*redout;
	t_lstcmd	*cmd_struct = malloc(sizeof(t_lstcmd));

	if (!cmd_struct)
		return (NULL);
	t_list	*curr;
	
	curr = cmd_lst;
	redin = NULL;
	redout = NULL;
	full_cmd = NULL;
	while (curr)
	{
		if (curr->next)
		{
			if (is_red(lst_getstr(curr)) == REDIN || is_red(lst_getstr(curr)) == HEREDOC)
			{
				ft_lstadd_back(&redin, ft_lstnew(ft_strdup(curr->content)));
				curr = curr->next;
				ft_lstadd_back(&redin, ft_lstnew(ft_strdup(curr->content)));
			}
			else if (is_red(lst_getstr(curr)) == REDOUT || is_red(lst_getstr(curr)) == APPEND)
			{
				ft_lstadd_back(&redout, ft_lstnew(ft_strdup(curr->content)));
				curr = curr->next;
				ft_lstadd_back(&redout, ft_lstnew(ft_strdup(curr->content)));
			}
			else
				ft_lstadd_back(&full_cmd, ft_lstnew(ft_strdup(curr->content)));
		}
		else
			ft_lstadd_back(&full_cmd, ft_lstnew(ft_strdup(curr->content)));
		curr = curr->next;
		///ft_lst clear(cmd_lst)   here or there
	}
	cmd_struct->full_cmd = full_cmd;
	cmd_struct->redin = redin;
	cmd_struct->redout = redout;
	return (cmd_struct);
}

void	print_token_struct(t_lstcmd *cmd_lst)
{
	if (!cmd_lst)
		return ;
	ft_putstr("The command is:  ");
	print_lst(cmd_lst->full_cmd);
	ft_putstr("The redirection in is:  ");
	print_lst(cmd_lst->redin);
	ft_putstr("The redirection out is:  ");
	print_lst(cmd_lst->redout);
	write(1, "\n", 1);
}

void	print_token_str(t_strcmd *cmd_str)
{
	int	i;

	if (!cmd_str)
		return ;
	i = 0;
	ft_putstr(GREEN "RED_IN :  " COLOR_END);
	print_tab(cmd_str->redin);
	ft_putstr(GREEN "RED_OUT:  " COLOR_END);
	print_tab(cmd_str->redout);
	ft_putstr(GREEN "CMD_TAB:  \n" COLOR_END);
	while (cmd_str->tab_cmd[i])
	{
		ft_putstr("          ");
		print_tab(cmd_str->tab_cmd[i]);
		i++;
	}
}

t_strcmd	*convert_to_str_token(t_lstcmd	*clean_tokens, int num_pipe)
{
	t_list	**partition;
	t_list	*part;
	t_strcmd	*str_token;

	partition = partition_lst(clean_tokens->full_cmd);
	str_token = malloc(sizeof(t_strcmd));
	if (!str_token)
		return (NULL);
	str_token->redin = lst_to_chatab(clean_tokens->redin);
	str_token->redout = lst_to_chatab(clean_tokens->redout);
	str_token->tab_cmd = malloc(sizeof(char **) * (num_pipe + 2));
	if(str_token->tab_cmd == NULL)
		return (NULL);
	int	i = 0;
	while (partition[i])
	{
		part = partition[i];
		str_token->tab_cmd[i] = lst_to_chatab(part);
		part = NULL;
		i++;
	}
	str_token->tab_cmd[i] = NULL;
	return (str_token);
}

void	parse_line(char *line)
{	
	char	*trimmed_line;
	t_list	*lst_tk;
	int		num_pipe;
	t_lstcmd	*clean_tokens;
	t_strcmd	*str_token;

	trimmed_line = ft_strtrim(line, " ");
	lst_tk = split_line(trimmed_line);
	num_pipe = count_pipe(lst_tk);
	if (check_token_err(lst_tk))
		return ;
	clean_tokens = tokenize_cmd(lst_tk);
	ft_lstclear(&lst_tk, &free);
	str_token = convert_to_str_token(clean_tokens, num_pipe);
	print_token_str(str_token);
	return;
}

// void	parse_line(char *line)
// {	
// 	char	*trimmed_line;
// 	t_list	*lst_tk;
// 	t_list	**partition;
// 	int		num_pipe;
// 	t_lstcmd	*clean_tokens;

// 	trimmed_line = ft_strtrim(line, " ");
// 	lst_tk = split_line(trimmed_line);
// 	num_pipe = count_pipe(lst_tk);
// 	//print_lst(lst_tk);

// 	if (check_token_err(lst_tk))
// 		return ;
// 	//printf("The number of pipe is %d\n", num_pipe);

// 	clean_tokens = tokenize_cmd(lst_tk);
// 	//print_token_struct(tokenize_cmd(lst_tk));
// 	ft_lstclear(&lst_tk, &free);
// 	partition = partition_lst(clean_tokens->full_cmd);

// 	t_strcmd	*str_token;
// 	str_token = malloc(sizeof(t_strcmd));
// 	if (!str_token)
// 		return ;
// 	str_token->redin = lst_to_chatab(clean_tokens->redin);
// 	str_token->redout = lst_to_chatab(clean_tokens->redout);
// 	str_token->tab_cmd = malloc(sizeof(char **) * (num_pipe + 2));
// 	if(str_token->tab_cmd == NULL)
// 		return ;
// 	int	i = 0;
// 	t_list	*part;
// 	while (partition[i])
// 	{
// 		part = partition[i];
// 		//print_lst(part);
// 		str_token->tab_cmd[i] = lst_to_chatab(part);
// 		part = NULL;
// 		i++;
// 	}
// 	str_token->tab_cmd[i] = NULL;
// 	print_token_str(str_token);

// 	return;
// }