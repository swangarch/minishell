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

#include "../includes/minishell.h"

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

int	get_tab_num(char **tab)
{
	int	i = 0;

	if (!tab)
		return (-1);
	while(tab[i])
		i++;
	return (i);
}

t_list *str_to_word_lst(char *cmd)
{
	t_list *lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst = split_line(cmd);
	//print_lst(lst);
	return (lst);
}

// typedef struct s_cmd
// {
// 	char **redin;
// 	char **redout;
// 	char **cmd;
// 	int	 has_in;
// 	int  has_out;
// }	t_cmd;

void init_cmd_struct(t_cmd *command)
{
	command->cmd = NULL;
	command->redin = NULL;
	command->redout = NULL;
	command->has_in = FALSE;
	command->has_out = FALSE;
}

void print_cmd(t_cmd *command)
{
	if (!command)
		return ;
	
	ft_putstr("RED IN : ");
	print_tab(command->redin);
	ft_putstr("\nRED OUT: ");
	print_tab(command->redout);
	ft_putstr("\nCMD    : ");
	print_tab(command->cmd);
	ft_putstr("\nHAS REDIN : ");
	ft_putnbr_fd(command->has_in, 1);
	ft_putstr("\nHAS REDOUT: ");
	ft_putnbr_fd(command->has_out, 1);
	ft_putstr("\n");
}

void print_multi_cmd(t_cmd **command)
{
	int	i;

	i = 0;
	if (!command)
		return ;
	while (command[i])
	{
		printf("The %d command is________________________ \n", i);
		print_cmd(command[i]);
		i++;
	}
}

t_cmd *create_cmd_from_lst(t_list *lst)
{
	t_cmd	*command;
	t_list	*cmd_lst;
	t_list	*redin;
	t_list	*redout;
	t_list	*curr;
	
	command = malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);
	init_cmd_struct(command);
	redin = NULL;
	redout = NULL;
	cmd_lst = NULL;///protect
	curr = lst;
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
				ft_lstadd_back(&cmd_lst, ft_lstnew(ft_strdup(curr->content)));
		}
		else if (is_red(lst_getstr(curr)) == REDIN || is_red(lst_getstr(curr)) == HEREDOC)
			ft_lstadd_back(&redin, ft_lstnew(ft_strdup(curr->content)));
		else if (is_red(lst_getstr(curr)) == REDOUT || is_red(lst_getstr(curr)) == APPEND)
			ft_lstadd_back(&redout, ft_lstnew(ft_strdup(curr->content)));
		else
			ft_lstadd_back(&cmd_lst, ft_lstnew(ft_strdup(curr->content)));
		curr = curr->next;
	}
	///ft_lst clear(cmd_lst) !!!!!!!!!!!!!!!!!!!!!!  here 
	//print_lst(cmd_lst);
	command->cmd = lst_to_chatab(cmd_lst);///protect
	command->redin = lst_to_chatab(redin);///protect
	command->redout = lst_to_chatab(redout);///protect
	if (command->redin[0])
		command->has_in = TRUE;
	if (command->redout[0])
		command->has_out = TRUE;
	if ((command->has_in || command->has_out) && !(command->cmd[0]))
	{
		command->cmd = malloc(sizeof(char *) * 2);
		command->cmd[0] = ft_strdup("");
		command->cmd[1] = NULL;
	}
	return (command);
}

t_cmd	**create_cmd_tab(char **tab)
{
	t_cmd	**tabcmd;
	t_list	*lst_command;
	int	num;
	int	i;

	if (!tab)
		return (NULL);
	num = get_tab_num(tab);
	tabcmd = malloc(sizeof(tabcmd) * (num + 1));
	if (!tabcmd)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		lst_command = str_to_word_lst(tab[i]);
		tabcmd[i] = create_cmd_from_lst(lst_command);
		//clear destroy lst_command and set to NULL
		i++;
	}
	tabcmd[i] = NULL;
	return (tabcmd);
}

int	red_next_err(char **tab)
{
	int	i;

	if (!tab)
		return (-1);
	i = 0;
	while (tab[i])
	{
		if (is_red(tab[i]) != TEXT)//&& !is_red(tab[i + 1]) == WORD)
		{
			if (!tab[i + 1] || is_red(tab[i + 1]) != TEXT)
			{
				ft_err(ERR_PREF "syntax error near unexpected token `");
				if (tab[i + 1])
					ft_putstr_fd(tab[i + 1], 2);
					///next depends one pipe or new line
				ft_err("'\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	parse_error(t_cmd **cmds)
{
	int	i;

	i = 0;
	if (!cmds)
		return (-1);
	while (cmds[i])
	{
		if (!(cmds[i]->has_in) && !(cmds[i]->has_out) && !(cmds[i]->cmd[0]))
		{
			ft_err(ERR_PREF "syntax error near unexpected token `|'\n");
			return (1);
		}
		if (red_next_err(cmds[i]->redin) || red_next_err(cmds[i]->redout))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_cmdtab_num(t_cmd **cmd_tab)
{
	int	i = 0;

	if (!cmd_tab)
		return (-1);
	while(cmd_tab[i])
		i++;
	return (i);
}

t_cmd	**parse_line(char *line)
{	
	char **tab_str;
	t_cmd **tab_cmd;

	tab_str = ft_split(line, '|');
	tab_cmd = create_cmd_tab(tab_str);
	///destroy
	if (parse_error(tab_cmd) || !tab_cmd)
		return (NULL);
	//print_multi_cmd(tab_cmd);

	return(tab_cmd);
}