CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g
NAME = minishell
READLINE = -L/Users/hoigag/.brew/opt/readline/lib -lreadline
LIBFT = -L./libft -lft

BUILIN_SRCS = builtins/ft_echo.c builtins/ft_env.c builtins/ft_pwd.c builtins/ft_cd.c builtins/ft_export_unset.c builtins/ft_exit.c builtins/exec_builtin.c
PARSING_SRCS = parsing/expand.c parsing/parsing_utils.c parsing/parsing.c parsing/tokenizer.c parsing/parser_utils.c
ENV_SCRS = env/env.c env/env_utils.c

SRCS = main.c  error_handler.c array_utils.c $(BUILIN_SRCS) $(PARSING_SRCS) $(ENV_SCRS)
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