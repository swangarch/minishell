#gcc -g *.c -Wall -Wextra -Werror -lreadline -I. -o minishell
cc -no-pie *.c libft.a -lreadline -I. -o minishell
