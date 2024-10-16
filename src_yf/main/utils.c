#include "../includes/minishell.h"

int str_to_ll(const char *str, long long *val)
{
    long long result;
    int sign;

    if (str == NULL || *str == '\0')
        return (FALSE);
    if (!ft_strcmp(str, "-9223372036854775808"))
    {
        *val = -9223372036854775552LL;
        return (TRUE);
    }
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
        result = result * 10 + *str - '0';
        str++;
    }
    if (*str)
        return (FALSE);
    *val = result * sign;
    return (TRUE);
}

int     is_numeric(const char *str)
{
    if (str == NULL || *str == '\0')
    {
        return (0);
    }
    if (str[0] == '-' && !str[1])
        return (0);
    if (str[0] == '-')
    {
        str++;
    }
    while (*str)
    {
        if (!ft_isdigit(*str))
        {
            return (0);
        }
        str++;
    }
    return (1);
}
