NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra

HEADER = minishell.h
LIBFT_HEADER = libft/libft.h

LIBGC = libgc/libgc.a
LIBGC_HEADER = libgc/include/gc.h

SRC_FILE =	main.c \
			parsing/append_utils.c \
			parsing/constructors.c \
			parsing/parse.c \
			parsing/parsing_utils1.c \
			parsing/parsing_utils2.c \
			parsing/parsing_utils3.c \
			parsing/parsing_utils4.c \
			utils/utils1.c \
			utils/utils2.c \
			utils/utils3.c \
			utils/utils4.c \
			utils/utils5.c \
			execute/exec.c \
			execute/redirection.c \
			execute/exec_handler.c \
			execute/execute.c \
			builtins/cd.c \
			builtins/echo.c \
			builtins/pwd.c \
			builtins/env.c \
			builtins/ft_exit.c \
			builtins/export.c \
			builtins/unset.c \


OBJ_FILE = $(SRC_FILE:.c=.o)

LIBFT_MAKEFILE_PATH = libft/ 
LIBFT = libft/libft.a

RL_DIR =  $(addprefix $(shell brew --prefix readline), /)

all : $(NAME)

debug: CFLAGS+=-g
debug: clean all

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I. -Ilibft -Ilibgc/include -I $(addprefix $(RL_DIR), include)
# -I$(shell brew --prefix readline)/include

$(NAME): $(OBJ_FILE) $(LIBGC) $(LIBFT) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ_FILE) $(LIBFT) $(LIBGC) -lreadline -L $(addprefix $(RL_DIR), lib) -o $(NAME)
# -L$(shell brew --prefix readline)/lib

$(LIBFT): $(LIBFT_HEADER)
	make -C $(LIBFT_MAKEFILE_PATH)

$(LIBGC): $(LIBGC_HEADER)
	make -C libgc/

clean :
	rm -rf $(OBJ_FILE) 
	make clean -C $(LIBFT_MAKEFILE_PATH)

fclean : clean
	rm -rf $(NAME) $(LIBFT)

re : fclean all