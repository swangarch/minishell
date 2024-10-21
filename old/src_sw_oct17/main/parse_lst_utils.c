/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:56:01 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/08 12:56:04 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_list	**partition_lst(t_list *lst_tk)
// {
// 	t_list	**partition;
// 	t_list	*curr_quick;
// 	t_list	*curr_slow;
// 	int		num_cmd;

// 	int		i = 0;
// 	if (!lst_tk)
// 		return (NULL);
// 	while (!ft_strcmp((char*)(lst_tk->content), "|") && lst_tk->next)
// 		lst_tk = lst_tk->next;
// 	num_cmd = count_pipe(lst_tk) + 1;
// 	partition = (t_list **)malloc(sizeof(t_list *) * (num_cmd + 1));
// 	if (!partition)
// 		return (NULL);//protect
// 	curr_quick = lst_tk;
// 	partition[i] = curr_quick;
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
// 				i++;
// 				partition[i] = curr_quick;
// 			}
// 		}
// 	}
// 	i++;
// 	partition[i] = NULL;
//  	return (partition);
// }

// t_list	**partition_lst(t_list *lst_tk)
// {
// 	t_list	**partition;
// 	t_list	*curr_quick;
// 	t_list	*curr_slow;
// 	int		num_cmd;

// 	int		i = 0;
// 	if (!lst_tk)
// 		return (NULL);
	
// 	if (count_pipe(lst_tk) == 0)
// 	{
// 		partition = (t_list **)malloc(sizeof(t_list *) * 2);
// 		if (!partition)
// 			return (NULL);
// 		partition[0] = ft_lstnew(ft_strdup(""));
// 		if (!partition[0])
// 			return (NULL);
// 		partition[1] = NULL;
// 	}

// 	while (!ft_strcmp((char*)(lst_tk->content), "|") && lst_tk->next)
// 		lst_tk = lst_tk->next;
// 	num_cmd = count_pipe(lst_tk) + 1;
// 	partition = (t_list **)malloc(sizeof(t_list *) * (num_cmd + 1));
// 	if (!partition)
// 		return (NULL);//protect
// 	curr_quick = lst_tk;
// 	partition[i] = curr_quick;
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
// 				i++;
// 				partition[i] = curr_quick;
// 			}
// 		}
// 	}
// 	i++;
// 	partition[i] = NULL;
//  	return (partition);
// }

t_list	**on_void_cmd(void)
{
	t_list	**partition;
	
	partition = (t_list **)malloc(sizeof(t_list *) * 2);
	if (!partition)
		return (NULL);
	partition[0] = ft_lstnew(ft_strdup(""));
	partition[1] = NULL;
	return (partition);
}

t_list	**partition_lst(t_list *lst_tk)
{
	t_list	**partition;
	t_list	*curr_quick;
	t_list	*curr_slow;
	int		num_cmd;

	int		i = 0;
	if (!lst_tk)
		return (on_void_cmd());

	num_cmd = count_pipe(lst_tk) + 1;
	partition = (t_list **)malloc(sizeof(t_list *) * (num_cmd + 1));
	if (!partition)
		return (NULL);//protect

	while (!ft_strcmp(lst_getstr(lst_tk), "|") && lst_tk->next)
	{
		partition[i] = ft_lstnew(ft_strdup(""));
		if (!partition[i])
		{
			//clear partition i and free the partition
			return (NULL);
		}
		i++;
		lst_tk = lst_tk->next;
	}
	
	curr_quick = lst_tk;
	partition[i] = curr_quick;
	while (curr_quick)
	{
		curr_slow = curr_quick;
		curr_quick = curr_quick->next;
		if (curr_quick && !ft_strcmp((char*)(curr_quick->content), "|"))
		{
			curr_slow->next = NULL;
			if(curr_quick->next && ft_strcmp((char*)(curr_quick->next->content), "|")) //pipe with cmd behind
			{
				curr_quick = curr_quick->next;
				i++;
				partition[i] = curr_quick;
			}
			else if(curr_quick->next && !ft_strcmp((char*)(curr_quick->next->content), "|")) //Multiple pipe 
			{
				curr_quick = curr_quick->next;
				i++;
				partition[i] = ft_lstnew(ft_strdup(""));
			}
		}
	}
	i++;
	partition[i] = NULL;
 	return (partition);
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

char	*lst_getstr(t_list *lst)
{
	if (!lst)
		return (NULL);
	return ((char *)lst->content);
}
