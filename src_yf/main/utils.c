#include "../includes/minishell.h"

int str_to_ll(const char *str, long long *val)
{
    long long result;
    int sign;

    if (str == NULL || *str == '\0')
        return (FALSE);
    if (!ft_strcmp(str, "-9223372036854775808"))
        return (*val = -9223372036854775552LL, TRUE);
    result = 0;
    sign = 1;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (ft_isdigit(*str))
    {
        if (result * 10 + *str - '0' < result)
            return (FALSE);
        result = result * 10 + *str++ - '0';
    }
    if (*str)
        return (FALSE);
    *val = result * sign;
    return (TRUE);
}

int     is_numeric(const char *str)
{
    if (str == NULL || *str == '\0')
        return (0);
    if (str[0] == '-' && !str[1])
        return (0);
    if (str[0] == '-')
        str++;
    while (*str)
    {
        if (!ft_isdigit(*str))
            return (0);
        str++;
    }
    return (1);
}

char    **split_by_equal(const char *s)
{
    char    **ptr;
    int     i;

    i = 0;
    ptr = (char **)malloc(2 * sizeof(char *));
    if (!ptr)
        return (NULL);
    while (s[i])
    {
        if (s[i] == '=')
            break ;
        ++i;
    }
    ptr[0] = ft_substr(s, 0, i);
    if (!ptr[0])
        return (free(ptr), NULL);
    if (!s[i])
        ptr[1] = ft_strdup("");
    else
        ptr[1] = ft_substr(s, i + 1, ft_strlen(s) - i - 1);
    if (!ptr[1])
        return (free(ptr[0]), free(ptr), NULL);
    return (ptr);
}

int	    ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void    set_close(int *fds)
{
    if (fds[0] >= 0)
	{
		close(fds[0]);
		fds[0] = -1;
	}
	if (fds[1] >= 0)
	{
		close(fds[1]);
		fds[1] = -1;
	}
}
