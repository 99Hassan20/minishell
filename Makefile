CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = minishell
READLINE = -L/Users/hoigag/.brew/opt/readline/lib -lreadline
LIBFT = -L./libft -lft
SRCS = main.c list_utils.c parsing.c parsing_utils.c error_handler.c\
	env.c env2.c expand.c builtins.c array_utils.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C libft all
	$(CC) $(CFLAGS) $(READLINE) $(LIBFT) $^ -o $@

clean:
	make -C libft clean
	rm -f *.o

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)