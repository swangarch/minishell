# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 17:20:13 by yfan              #+#    #+#              #
#    Updated: 2024/10/29 19:05:56 by yfan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

# Directories
LIBFT		=	libft/libft.a
INC			=	includes
SRCS_DIR		=	srcs

INIT_DIR	= 	initialization
BUILTIN_DIR	=	builtin
EXEC_DIR  	=   execution
LEXER_DIR	= 	lexer
UTILS_DIR   = 	utils
PARSING_DIR = 	parsing
REDIR_DIR   = 	redirection
EXPAND_DIR  =   expansion

# sources
INIT_SRCS	= 	$(INIT_DIR)/init.c $(INIT_DIR)/environne.c $(INIT_DIR)/env_utils.c $(INIT_DIR)/prompt.c

BUILTIN_SRCS=	$(BUILTIN_DIR)/builtin.c $(BUILTIN_DIR)/check_builtin.c $(BUILTIN_DIR)/mini_cd.c \
	$(BUILTIN_DIR)/mini_echo.c $(BUILTIN_DIR)/mini_export.c $(BUILTIN_DIR)/set_pwd.c $(BUILTIN_DIR)/set_var.c $(BUILTIN_DIR)/export_utils.c

EXEC_SRCS  	=   $(EXEC_DIR)/execute.c $(EXEC_DIR)/execute_path.c $(EXEC_DIR)/execute_utils.c

LEXER_SRCS	= 	$(LEXER_DIR)/lexer.c $(LEXER_DIR)/lexer_check.c

UTILS_SRCS   = 	$(UTILS_DIR)/error.c $(UTILS_DIR)/free.c $(UTILS_DIR)/free_env.c $(UTILS_DIR)/signal.c $(UTILS_DIR)/str_utils.c $(UTILS_DIR)/utils.c

PARSING_SRCS = 	$(PARSING_DIR)/parse_cmd_from_lst.c $(PARSING_DIR)/parse_create_cmd.c $(PARSING_DIR)/parse_func.c \
	$(PARSING_DIR)/parse_labels.c $(PARSING_DIR)/parse_split.c $(PARSING_DIR)/parse_token_err.c $(PARSING_DIR)/parse_utils.c

REDIR_SRCS   = 	$(REDIR_DIR)/redir_in.c $(REDIR_DIR)/redir_out.c $(REDIR_DIR)/heredoc_process.c $(REDIR_DIR)/heredoc_utils.c

EXPAND_SRCS  =   $(EXPAND_DIR)/expansion.c $(EXPAND_DIR)/expansion_general.c $(EXPAND_DIR)/expansion_here.c $(EXPAND_DIR)/expansion_utils.c

SRCS		=	$(SRCS_DIR)/minishell.c $(SRCS_DIR)/minishell_loop.c \
				$(addprefix $(SRCS_DIR)/, $(INIT_SRCS)) \
				$(addprefix $(SRCS_DIR)/, $(BUILTIN_SRCS)) \
				$(addprefix $(SRCS_DIR)/, $(EXEC_SRCS)) \
				$(addprefix $(SRCS_DIR)/, $(LEXER_SRCS)) \
				$(addprefix $(SRCS_DIR)/, $(UTILS_SRCS)) \
				$(addprefix $(SRCS_DIR)/, $(PARSING_SRCS)) \
				$(addprefix $(SRCS_DIR)/, $(REDIR_SRCS)) \
				$(addprefix $(SRCS_DIR)/, $(EXPAND_SRCS)) \

OBJS_DIR		=	objs

OBJS		=	$(SRCS:%.c=$(OBJS_DIR)/%.o)

#Compiler and CFlags
CC			=	cc 
CFLAGS		=	-Wall -Wextra -Werror
CFLAGS		+=	-I libft -Iinclude
LDFLAGS     = 	-lreadline
RM			=	rm -f

# Colors
YELLOW		=	\033[1;33m
GREEN		=	\033[1;32m
RESET		=	\033[0m

# Build rules
all:		$(NAME)

$(LIBFT):
		@echo "$(YELLOW)Building libft...$(RESET)"
		@make -sC ./libft
		@echo "$(GREEN)libft built successfully!$(RESET)"

$(NAME):	$(OBJS) $(LIBFT)
		@echo "$(YELLOW)Linking $(NAME) executable...$(RESET)"
		@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)
		@echo "$(GREEN)Executable $(NAME) created successfully!$(RESET)"

$(OBJS_DIR)/%.o:	%.c
		@mkdir -p $(dir $@)
		@echo "$(YELLOW)Compiling $<...$(RESET)"
		@$(CC) $(CFLAGS) -c $< -o $@
		@echo "$(GREEN)Compiled $< successfully!$(RESET)"

clean:
		@echo "$(YELLOW)Cleaning object files...$(RESET)"
		@$(RM) -r $(OBJS)
		@$(RM) -r $(OBJS_DIR)
		@make clean -sC ./libft
		@echo "$(GREEN)Object files cleaned!$(RESET)"

fclean:		clean
		@echo "$(YELLOW)Removing $(NAME) executable...$(RESET)"
		@$(RM) $(NAME)
		@$(RM) $(LIBFT)
		@echo "$(GREEN)Executable removed successfully!$(RESET)"

re:		fclean all

# Phony targets represent actions instead of files
.PHONY:		all clean fclean re
