CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g
NAME = minishell
READLINE = -lreadline #-L/Users/hoigag/.brew/opt/readline/lib 
LIBFT = -L./libft -lft

BUILIN_SRCS = $(addprefix builtins/, ft_echo.c ft_env.c ft_pwd.c ft_cd.c ft_export_unset.c ft_exit.c exec_builtin.c)
PARSING_SRCS = $(addprefix parsing/, expand.c parsing_utils.c parsing.c tokenizer.c parser_utils.c parse_redirections.c)
ENV_SCRS = $(addprefix env/, env.c env_utils.c)

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