#include "../../includes/minishell.h"

void    free_before_exit(t_shell *shell)
{
    
}

void	free_char_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_env(t_env *head)
{
	t_env	*next;

	while (head != NULL)
	{
		next = head->next;
		free(head->var_name);
		free(head->content);
		free(head);
		head = next;
	}
}

void	free_env_path(char **env, char *get_path)
{
	free(get_path);
	free(env[0]);
    free(env[1]);
    free(env[2]);
    free(env[3]);
    free(env);
}
