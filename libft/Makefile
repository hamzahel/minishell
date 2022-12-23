# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omoussao <omoussao@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/21 16:49:39 by hel-ayac          #+#    #+#              #
#    Updated: 2022/03/27 00:17:54 by omoussao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libft.a
SRCS= ft_isalnum.c ft_isascii.c ft_isprint.c ft_memcmp.c  ft_putendl_fd.c ft_split.c   ft_strdup.c  ft_strlcat.c ft_strlen.c \
	ft_atoi.c ft_isalpha.c ft_isdigit.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c  ft_strchr.c  ft_strjoin.c ft_strlcpy.c ft_strncmp.c \
	ft_bzero.c ft_memset.c ft_strrev.c

OBJ= $(SRCS:.c=.o)

INCLUDE= libft.h

FLG= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	@ar rcs $(NAME) $(OBJ)
	@echo "archive all data of $(NAME)"

clean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -f $(OBJB)
	@echo "clean"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "fclean"

%.o: %.c
	gcc $(FLG) -c $< -I $(INCLUDE)

re: fclean all
