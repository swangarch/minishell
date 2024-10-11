#include "../../includes/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INIT_SIZE 64    // 初始的缓冲区大小
#define GROWTH_FACTOR 2 // 增长因子

// 模拟存储上一次命令的退出状态
int last_exit_status = 0; // 你需要在命令执行后更新这个值

// 手动扩展内存函数，模仿 realloc
char *expand_buffer(char *old_buffer, int *capacity)
{
    int new_capacity = (*capacity) * GROWTH_FACTOR;
    char *new_buffer = malloc(new_capacity); // 分配新内存
    if (!new_buffer)
    {
        free(old_buffer); // 如果分配失败，释放旧的内存
        return NULL;
    }
    memcpy(new_buffer, old_buffer, *capacity); // 将旧数据复制到新内存
    free(old_buffer);                          // 释放旧内存
    *capacity = new_capacity;                  // 更新容量
    return new_buffer;                         // 返回新的内存块指针
}

// 用于将字符串追加到结果中，处理内存不足的情况
void append_str(char **result, int *len, int *capacity, const char *str)
{
    int str_len = strlen(str);
    while (*len + str_len >= *capacity)
    {
        *result = expand_buffer(*result, capacity);
        if (!*result)
        {
            perror("Memory allocation failed");
            exit(1);
        }
    }
    strcpy(*result + *len, str);
    *len += str_len;
}

int     init_expansion(t_expansion *exp)
{
    
}

char    *expand_var(const char *input)
{
    t_expansion exp;

    if (!init_expansion(&exp))
        return (NULL);
    while (input[i] != '\0')
    {
        if (input[i] == '\'')
        {
            in_single_quote = !in_single_quote;
            result[len++] = input[i++];
        }
        else if (input[i] == '"')
        {
            in_double_quote = !in_double_quote;
            result[len++] = input[i++];
        }
        else if (input[i] == '$' && !in_single_quote)
        {
            i++;
            if (input[i] == '?')
            {
                // 处理 $?
                i++; // 跳过 '?'
                char exit_status[12];
                sprintf(exit_status, "%d", last_exit_status); // 转换状态码为字符串
                append_str(&result, &len, &capacity, exit_status);
            }
            else if (input[i] == '{')
            {
                i++; // 跳过 '{'
                char var_name[256];
                int k = 0;
                while (input[i] && input[i] != '}')
                {
                    var_name[k++] = input[i++];
                }
                var_name[k] = '\0';
                if (input[i] == '}')
                    i++; // 跳过 '}'

                // 处理 ${?}
                if (strcmp(var_name, "?") == 0)
                {
                    char exit_status[12];
                    sprintf(exit_status, "%d", last_exit_status);
                    append_str(&result, &len, &capacity, exit_status);
                }
                else
                {
                    // 处理其他 ${var_name}
                    char *env_value = getenv(var_name);
                    if (env_value)
                    {
                        append_str(&result, &len, &capacity, env_value);
                    }
                }
            }
            else if (isalnum(input[i]) || input[i] == '_')
            {
                // 处理 $var_name
                char var_name[256];
                int k = 0;
                while (input[i] && (isalnum(input[i]) || input[i] == '_'))
                {
                    var_name[k++] = input[i++];
                }
                var_name[k] = '\0';
                if (k > 0)
                {
                    char *env_value = getenv(var_name);
                    if (env_value)
                    {
                        append_str(&result, &len, &capacity, env_value);
                    }
                }
            }
        }
        else
        {
            result[len++] = input[i++];
        }

        // 如果 result 长度超出 capacity，需要扩展内存
        if (len >= capacity)
        {
            result = expand_buffer(result, &capacity);
            if (!result)
            {
                perror("Memory allocation failed");
                exit(1);
            }
        }
    }

    result[len] = '\0'; // 结束符
    return result;
}
