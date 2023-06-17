CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = minishell
READLINE = -L/Users/hoigag/.brew/opt/readline/lib -lreadline
LIBFT = -L./libft -lft

BUILIN_SRCS = builtins/ft_echo.c builtins/ft_env.c builtins/ft_pwd.c builtins/ft_cd.c builtins/ft_export_unset.c builtins/ft_exit.c 

SRCS = main.c list_utils.c parsing.c parsing_utils.c error_handler.c\
	env.c env2.c expand.c builtins.c array_utils.c $(BUILIN_SRCS)
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C libft all
	$(CC) $(CFLAGS) $(READLINE) $(LIBFT) $^ -o $@

clean:
	make -C libft clean
	rm $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)