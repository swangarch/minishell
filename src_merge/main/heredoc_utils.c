#include "../includes/minishell.h"

static char *join_here_doc_name(int count, int index_p)   ///////////////////safe with no leaks
{
    char *filename;
    char *basename;
    char *strnum;
    char *heredocnum;
    char *here_doc_name;

    basename = "/tmp/.heredoc++-+-+-+--+";
    strnum = ft_itoa(count);
    if (!strnum)
        return (NULL);
    heredocnum = ft_itoa(index_p);
    if (!heredocnum)
    {
        free(strnum);
        return (NULL);
    }
    here_doc_name = ft_str4join(basename, strnum, "_", heredocnum);
    free(strnum);
    free(heredocnum);
    return (here_doc_name);
}

char *here_doc_name(int index_p)  ///////////////////safe with no leaks
{
    int fd_heredoc;
    char *filename;
    int count;
    char *strnum;

    count = 0;
    filename = join_here_doc_name(count, index_p);
    if (!filename)
        return (NULL);
    while (access(filename, F_OK) == 0)
    {
        count++;
        free(filename);
        filename = join_here_doc_name(count, index_p);
        if (!filename)
            return (NULL);
    }
    return (filename);
}

int has_heredoc(t_cmd *cmd, t_shell *shell)  ///////////////////safe with no leaks
{
    int i;

    i = 0;
    if (!cmd || !shell)
        return (0);
    while (cmd->redin[i])
    {
        if (is_red(cmd->redin[i]) == HEREDOC)
            return (1);
        i++;
    }
    return (0);
}

void delete_heredoc(char **here_docs)  ///////////////////safe with no leaks
{
    int i;

    if (!here_docs)
        return ;
    i = 0;
    while (here_docs[i])
    {
        if (ft_strcmp("", here_docs[i]) && access(here_docs[i], F_OK) == 0)
            unlink(here_docs[i]);
        free(here_docs[i]);
        here_docs[i] = NULL;
        i++;
    }
    free(here_docs);
    here_docs = NULL;
}
