#include "../includes/minishell.h"

char	**env_list_to_char(t_env *env)
{
	char	**result;
	int		size;
	int		i;

	i = 0;
	size = get_env_list_size(env);
	result = malloc(sizeof(char *) * (size + 1));
	result[size] = NULL;
	while (env != NULL && i < size)
	{
		result[i] = get_full_env(env);
		env = env->next;
		i++;
	}
	return (result);
}

int     get_env_list_size(t_env *head)
{
	t_env	*curr;
	int		i;

	i = 0;
	curr = head;
	while (curr != NULL)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}

char	*get_full_env(t_env *env)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(env->var_name, "=");
	if (env->content != NULL)
	{
		result = ft_strjoin(tmp, env->content);
		free(tmp);
	}
	else
		return (tmp);
	return (result);
}

char    *mini_get_env(const char *name, t_env *lst_env)
{
    while (lst_env)
    {
        if (!ft_strcmp(lst_env->var_name, name))
            return (ft_strdup(lst_env->content));
        lst_env = lst_env->next;
    }
    return (ft_strdup(""));
}

void	unset_var(t_env **lst_env, const char *name)
{
	t_env	*prev;
	t_env	*current;

	current = *lst_env;
	while (!ft_strcmp(current->var_name, name))
	{
		free(current->content);
		free(current->var_name);
		*lst_env = current->next;
		free(current);
		current = *lst_env;
	}
	prev = current;
	current = current->next;
	while (current)
    {
        if (!ft_strcmp(current->var_name, name))
        {
			free(current->content);
			free(current->var_name);
			prev->next = current->next;
			free(current);
			current = prev;
		}
		prev = current;
        current = current->next;
    }
}

void	set_var(t_env **lst_env, char **name, char *cmd)
{
	t_env	*current;
	t_env	*new;

	current = *lst_env;
	if (!current)
	{
		new = init_env_node(cmd);
		if (!new)
		{
			return ;
		}
		current = new;
		return ;
	}
	while (current)
    {
        if (!ft_strcmp(current->var_name, name[0]))
        {
			free(current->content);
			current->content = ft_strdup(name[1]);
			return ;
		}
        current = current->next;
    }
	if (!current)
	{
		new = init_env_node(cmd);
		if (!new)
		{
			return ;
		}
		add_back_env_node(lst_env, new);
	}
}

void	set_pwd(t_env **lst_env, char *name, char *content)
{
	t_env	*current;
	t_env	*new;
	char	*tmp_old;
	char	*tmp_new;

	current = *lst_env;
	tmp_old = ft_strjoin(name, "=");
	tmp_new = ft_strjoin(tmp_old, content);
	free(tmp_old);
	if (!current)
	{
		new = init_env_node(tmp_new);
		if (!new)
		{
			free(tmp_new);
			return ;
		}
		current = new;
		free(tmp_new);
		return ;
	}
	while (current)
    {
        if (!ft_strcmp(current->var_name, name))
        {
			free(current->content);
			current->content = ft_strdup(content);
			free(tmp_new);
			return ;
		}
        current = current->next;
    }
	if (!current)
	{
		new = init_env_node(tmp_new);
		if (!new)
		{
			free(tmp_new);
			return ;
		}
		add_back_env_node(lst_env, new);
		free(tmp_new);
	}
}
