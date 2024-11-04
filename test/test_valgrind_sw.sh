cd ../minishell_sw
make

valgrind --leak-check=full --suppressions=../test/readline.supp --show-leak-kinds=all --track-fds=yes --trace-children=yes ./minishell
