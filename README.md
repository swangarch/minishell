# Minishell

Minishell is a school 42 project to implement a simplified version of the bash. 
It mimics essential Bash behaviors including command parsing, piping, redirections, and built-in commands — all written in C without using any external libraries， only our own libft and minimum syscalls are allowed.

---
## Objectives
- Understand how bash works.
- Master key system calls: `fork`, `execve`, `pipe`, `dup2`, `wait`, `signal`
- Handle complex user inputs with a custom lexer and parser
- Manage memory manually and responsibly
- Handle interactive terminal behavior and signals
- Handle built-in commands
---

## Features

### Command Line Parsing and Expansion

- Handle spaces, quotes, escapes, and delimiters
- Environment variable expansion (e.g., `$PATH`, `$?`)
- Correct treatment of single `'` and double `"` quotes

### Pipe

Supports chaining multiple commands using `|`:

ls -l | grep .c | wc -l

### Redirections
Input redirection: < file
Output redirection (overwrite): > file
Output redirection (append): >> file

cat < input.txt > output.txt

### Here Document (heredoc)
Input is read until a delimiter:

cat << EOF
line 1
line 2
ctrl + d(EOF)

### Syntax Error Checking
Handles basic command-line syntax issues:

minishell$ ls | | wc
minishell: syntax error near unexpected token `|`

### Signal Handling

Ctrl + C → interrupts running command (SIGINT)
Ctrl + \ → ignored (SIGQUIT)
Ctrl + D → exits shell cleanly (EOF)

### Built-in Commands
Implemented internally without execve:

echo support -n
pwd
cd
env support . .. ~ -
export
unset
exit

### Build Instructions
Requirements
OS: Linux(tested on ubuntu with clang)
Tools: Makefile

1. Clone the repo
2. Run make
3. Run ./minishell
4. Type your command

example:
minishell$ echo Hello World
Hello World

minishell$ export NAME=hello
minishell$ echo "$NAME world"
hello world

minishell$ ls -l > result.txt
To exit:
minishell$ exit or ctrl + d with nothing typed in the prompt

### Memory & Resource Management
No memory & fd leaks (validated with valgrind)

📁 License
This project is for educational purposes at 42 School. No license is provided.
