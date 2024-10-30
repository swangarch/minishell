# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shuwang <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 17:07:09 by shuwang           #+#    #+#              #
#    Updated: 2024/06/01 17:28:42 by shuwang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -I.

HEADER = libft.h

SRCS = ft_atoi.c ft_memchr.c ft_split.c ft_strncmp.c \
	ft_bzero.c ft_memcmp.c ft_strchr.c ft_strnstr.c \
	ft_calloc.c ft_memcpy.c ft_strdup.c ft_strrchr.c \
	ft_isalnum.c ft_memmove.c ft_striteri.c ft_strtrim.c \
	ft_isalpha.c ft_memset.c ft_strjoin.c ft_substr.c \
	ft_isascii.c ft_putchar_fd.c ft_strlcat.c ft_tolower.c \
	ft_isdigit.c ft_putendl_fd.c ft_strlcpy.c ft_toupper.c \
	ft_isprint.c ft_putnbr_fd.c ft_strlen.c ft_itoa.c \
	ft_putstr_fd.c ft_strmapi.c ft_lstsize.c ft_lstadd_back.c \
	ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
	ft_lstlast.c ft_lstmap.c ft_lstnew.c get_next_line.c \
	get_next_line_utils.c ft_printf.c ft_putchar_ptf.c ft_putnbr_ptf.c \
	ft_putptr_ptf.c ft_putstr_ptf.c ft_putunbr_ptf.c ft_putx_ptf.c \
	ft_strcmp.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
