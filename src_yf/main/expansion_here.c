#include "../includes/minishell.h"

char    *expand_var_here(char *input, t_env *lst_env, int status)
{
    t_expansion exp;

    if (!input)
        return (NULL);
    if (!init_expansion(&exp))
        return (free(input), NULL);
    while (input[exp.i] != '\0')
    {
        if (!handle_quotes(input, &exp))
            continue;
        else if (input[exp.i] == '$' && valid_exp(input[exp.i + 1]))
        {
            if (!handle_dollar(input, &exp, lst_env, status))
                return (free(input), free(exp.result), NULL);
        }
        else
            exp.result[exp.len++] = input[exp.i++];
        if (exp.len >= exp.size && !handle_buffer(&exp))
            return (free(input), NULL);
    }
    exp.result[exp.len] = '\0';
    return (free(input), exp.result);
}
// char    *expand_var_here(char *input, t_env *lst_env, int status)
// {
//     t_expansion exp;

//     if (!input)
//         return (NULL);
//     if (!init_expansion(&exp))
//         return (NULL);
//     while (input[exp.i] != '\0')
//     {
//         if (input[exp.i] == '\'' && !exp.in_dquote)
//         {
//             exp.in_squote = !exp.in_squote;
//             //exp.result[exp.len++] = input[exp.i++];
//             exp.i++;
//         }
//         else if (input[exp.i] == '"' && !exp.in_squote)
//         {
//             exp.in_dquote = !exp.in_dquote;
//             //exp.result[exp.len++] = input[exp.i++];
//             exp.i++;
//         }
//         else if (input[exp.i] == '$' && valid_exp(input[exp.i + 1]))
//         {
//             exp.i++;
//             if (input[exp.i] == '?')
//             {
//                 exp.i++;
//                 exp.exit_status = ft_itoa(status);
//                 if (!exp.exit_status || !append_str(&exp))
//                     return (free(exp.result), NULL);
//             }
//             else if (ft_isdigit(input[exp.i]))
//                 exp.i++;
//             else if (input[exp.i] == '{')
//             {
//                 exp.i++;
//                 exp.k = 0;
//                 while (input[exp.i] && input[exp.i] != '}')
//                     exp.var_name[exp.k++] = input[exp.i++];
//                 exp.var_name[exp.k] = '\0';
//                 if (input[exp.i] == '}')
//                     exp.i++;
//                 if (!ft_strcmp(exp.var_name, "?"))
//                 {
//                     exp.exit_status = ft_itoa(status);
//                     if (!exp.exit_status || !append_str(&exp))
//                         return (free(exp.result), NULL);
//                 }
//                 else
//                 {
//                     exp.env_val = mini_get_env(exp.var_name, lst_env);
//                     if (!exp.env_val || !append_env(&exp))
//                         return (free(exp.result), NULL);
//                 }
//             }
//             else if (ft_isalnum(input[exp.i]) || input[exp.i] == '_')
//             {
//                 exp.k = 0;
//                 while (ft_isalnum(input[exp.i]) || input[exp.i] == '_')
//                     exp.var_name[exp.k++] = input[exp.i++];
//                 exp.var_name[exp.k] = '\0';
//                 if (exp.k > 0)
//                 {
//                     exp.env_val = mini_get_env(exp.var_name, lst_env);
//                     if (!exp.env_val || !append_env(&exp))
//                         return (free(exp.result), NULL);
//                 }
//             }
//         }
//         else
//             exp.result[exp.len++] = input[exp.i++];
//         if (exp.len >= exp.size)
//         {
//             exp.result = expand_buffer(exp.result, &exp.size);
//             if (!exp.result)
//                 return (NULL);
//         }
//     }
//     exp.result[exp.len] = '\0';
//     return (free(input), exp.result);
// }
