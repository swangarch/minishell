#include "../includes/minishell.h"

void mini_execute(t_shell *shell, t_strcmd *str_cmd)
{
    int i;
    int j;
    pid_t pid;
    int *p_fd;

    if (str_cmd->num_cmd == 1)
    {
        if (is_build_in(str_cmd->tab_cmd[0][0]))
        {
            printf("deal one build-in\n");
        }
        // else
        // {
        //     pid = fork();
        //     if (pid == -1)
        //     {
        //         g_status = 3;
        //         perror("fork");
        //         return ;
        //     }
        //     else if (pid == 0)
        //         child_process();
        //     waitpid(pid, &g_status, 0);
        // }
        return;
    }
    p_fd = (int *)malloc(2 * (str_cmd->num_cmd - 1) * sizeof(int));
    if (!p_fd)
    {
        g_status = 1;
        ft_putstr_fd(MES_MALLOC_ERR, STDERR_FILENO);
        return;
    }
    i = 0;
    while (i < str_cmd->num_cmd - 1)
    {
        if (pipe(p_fd + i * 2) == -1)
        {
            g_status = 2;
            perror("pipe failed");
            free(p_fd);
            return;
        }
        ++i;
    }
    i = 0;
    while (i < str_cmd->num_cmd)
    {
        pid = fork();
        if (pid == -1)
        {
            g_status = 3;
            perror("fork");
            free(p_fd);
            return;
        }
        else if (pid == 0)
        {
            if (i > 0)
            {
                dup2(p_fd[(i - 1) * 2], 0);
            }
            if (i < str_cmd->num_cmd - 1)
            {
                dup2(p_fd[i * 2 + 1], 1);
            }
            j = 0;
            while (j < 2 * (str_cmd->num_cmd - 1))
            {
                close(p_fd[j++]);
            }
            execute(str_cmd->tab_cmd[i], shell->env);
        }
        ++i;
    }
    j = 0;
    while (j < 2 * (str_cmd->num_cmd - 1))
    {
        close(p_fd[j++]);
    }
    j = 0;
    while (j < str_cmd->num_cmd)
    {
        waitpid(-1, &g_status, 0);
        j++;
    }
    free(p_fd);
}

void	execute(char **cmd, char **env)
{
	char	*path;

	path = get_path(cmd[0], env);
	if (!path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	if (execve(path, cmd, env) == -1)
	{
		free(path);
		perror("execve");
        exit(126);
	}
	free(path);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*part_path;
	char	*full_path;
	char	**all_path;

	i = -1;
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	all_path = env_split(env);
	if (!all_path)
		return (NULL);
	while (all_path[++i])
	{
		part_path = ft_strjoin(all_path[i], "/");
		if (!part_path)
			return (free_char_array(all_path), NULL);
		full_path = ft_strjoin(part_path, cmd);
		if (!full_path)
			return (free_char_array(all_path), free(part_path), NULL);
		free(part_path);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_char_array(all_path), full_path);
		free(full_path);
	}
	return (free_char_array(all_path), NULL);
}

char	**env_split(char **env)
{
	int		i;
	char	**all_path;

	i = 0;
	while (env && env[i] && ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	if (!i)
		return (NULL);
	all_path = ft_split(env[i] + 5, ':');
	if (!all_path)
		return (NULL);
	return (all_path);
}
