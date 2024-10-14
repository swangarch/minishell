#gcc -g *.c -Wall -Wextra -Werror -lreadline -I. -o minishell
gcc -g *.c libft.a -lreadline -I. -o minishell
