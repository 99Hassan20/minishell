CC = cc
CFLAGS = -Wall -Werror -Wextra -I./includes #-fsanitize=address -g
NAME = minishell
READLINE =  -L/Users//.brew/opt/readline/lib -I/Users/hoigag/.brew/opt/readline/include
LIBFT = -L./libft -lft

RLFLGS    = -L/Users/hoigag/.brew/opt/readline/lib -lreadline
RLOFLGS   = -I/Users/hoigag/.brew/opt/readline/include

BUILIN_SRCS = $(addprefix builtins/, ft_echo.c ft_env.c ft_pwd.c ft_cd.c ft_export_unset.c ft_exit.c exec_builtin.c)
PARSING_SRCS = $(addprefix parsing/, expand.c parsing_utils.c lexer.c tokenizer.c parser_utils.c parse_redirections.c)
ENV_SCRS = $(addprefix env/, env.c env_utils.c)
EXEC_SRCS = $(addprefix execution/, 3d_split.c get_path.c tools.c file_path.c)
SRCS = main.c freee.c error_handler.c array_utils.c $(BUILIN_SRCS) $(PARSING_SRCS) $(ENV_SCRS) $(EXEC_SRCS) ft_malloc.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) 
	make -C libft all
	$(CC) $(CFLAGS) $(LIBFT) $(RLFLGS) -lreadline $^  -o $@

# %.o: %.c
# 	$(CC) $(CFLAGS) $(RLOFLGS) -c $< -o $@

clean:
	make -C libft clean
	rm $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)