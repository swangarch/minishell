#include "../includes/minishell.h"

void    write_heredoc(t_cmd *cmd, int *fd_infile, int *i, t_shell *shell)
{
    char *line;
    int index_fd = *i / 2;

    line = readline("> ");///free
    //add_history(line);
    line = expand_var_here(line, shell->env_head, shell->status);
    while (line && ft_strcmp(line, cmd->redin[*i]))
    {
        write(fd_infile[index_fd], line, ft_strlen(line));
        write(fd_infile[index_fd], "\n", 1);
        free(line);
        line = readline("> ");
        line = expand_var_here(line, shell->env_head, shell->status);
    }
    free(line);
}

int open_heredoc_creat(int *fd_infile, int *i, char *here_doc)
{
    int index_fd;

    index_fd = *i / 2;
    fd_infile[index_fd] = open(here_doc, O_WRONLY | O_CREAT, 0666);
    if (fd_infile[index_fd] < 0)
    {
        perror(here_doc);
        close_fds(fd_infile, *i);
        free(fd_infile);
        return (0);
    }
    return (1);
}

char *creat_heredoc(t_cmd *cmd, int *fd_infile, int *i, t_shell *shell, int index_p)//, char **here_docs)
{
    char *here_doc;
    int index_fd;

    index_fd = *i / 2;
    here_doc = here_doc_name(index_p);
    if (!here_doc)
        return (NULL);
    (*i)++;
    if (!open_heredoc_creat(fd_infile, i, here_doc))
        return (NULL);
    write_heredoc(cmd, fd_infile, i, shell);
    close(fd_infile[index_fd]);
    if (index_fd != get_tab_num(cmd->redin) / 2 - 1)//如果heredoc不是最后一个重定向in,删除heredoc 返回空字符串用来判断 
    {
        unlink(here_doc);
        free(here_doc);
        here_doc = NULL;
        return (ft_strdup(""));
    }
    return (here_doc);//如果heredoc是最后一个重定向in, 返回他的名字
}

char **process_heredocs(t_cmd **tab_cmd, t_shell *shell)
{
    int i;
    int *fd_infile;
    int num_cmd;
    int index_p;
    char **here_docs;

    index_p = 0;
    if (!tab_cmd || !shell)
        return (NULL);/////protect
    num_cmd = get_cmdtab_num(tab_cmd);
    here_docs = malloc(sizeof(char *) * (num_cmd + 1));
    if(!here_docs)
        return (NULL);
    while (index_p < num_cmd)
    {
        i = 0;
        fd_infile = malloc(get_tab_num(tab_cmd[index_p]->redin) * sizeof(int));  //table of fds
        if (!fd_infile)
        {
            ft_err(MES_MALLOC_ERR);
            //free
            return (NULL);
        }
        if (!has_heredoc(tab_cmd[index_p], shell))//如果这个命令没有一个red in, 那么给空字符串用于判断, 直接跳转到下个命令
        {
            here_docs[index_p] = ft_strdup("");
            if (!here_docs[index_p])
            {
                //free tab
                return (NULL);
            }
            index_p++;
            continue ;
        }
        while (tab_cmd[index_p]->redin[i])
        {
            if (is_red(tab_cmd[index_p]->redin[i]) == HEREDOC)
            {
                here_docs[index_p] = creat_heredoc(tab_cmd[index_p], fd_infile, &i, shell, index_p);
                if (!here_docs[index_p])//error
                {
                    //free clear tab
                    return (NULL);//return NULL
                }
                else if (!ft_strcmp("", here_docs[index_p]) && i / 2 != get_tab_num(tab_cmd[index_p]->redin) / 2 - 1)//check if here doc is not the last redin, if not free it, only keep the last one
                {
                    free(here_docs[index_p]);
                    here_docs[index_p] = NULL;
                }
            }
            i++;
        }//after this loop, if in each command splited by pipe, the last redirection is here doc, here_docs[index_p] should be name of heredoc, other wise is void string, 
        free(fd_infile);
        index_p++;
    }
    here_docs[index_p] = NULL;
    return (here_docs);
}