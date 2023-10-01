CC = cc
CFLAGS = -Wall -Werror -Wextra -I./includes #-fsanitize=address -g
NAME = minishell
READLINE =  -L/Users//.brew/opt/readline/lib -I/Users/hoigag/.brew/opt/readline/include
LIBFT = -L./libft -lft

RLFLGS    = -L/Users/hoigag/.brew/opt/readline/lib -lreadline
RLOFLGS   = -I/Users/hoigag/.brew/opt/readline/include

BUILIN_SRCS = $(addprefix builtins/, ft_echo.c ft_env.c ft_pwd.c ft_cd.c ft_export_unset.c ft_exit.c exec_builtin.c)
PARSING_SRCS = $(addprefix parsing/, printing.c expand.c expand_utils.c lexer_utils.c lexer.c tokenizer.c parser_utils.c parse_redirections.c parse_redirections2.c)
ENV_SCRS = $(addprefix env/, env.c env_utils.c)
EXEC_SRCS = $(addprefix execution/, 3d_split.c tools.c file_path.c r_red.c l_red.c herdocs.c exectio_err.c whiout_cmd.c)
SRCS = main.c freee.c freee2.c error_handler.c array_utils.c $(BUILIN_SRCS) $(PARSING_SRCS) $(ENV_SCRS) $(EXEC_SRCS)
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) 
	make -C libft all
	$(CC) $(CFLAGS) $(LIBFT) $(RLFLGS) $^  -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(RLOFLGS) -c $< -o $@

clean:
	make -C libft clean
	rm $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)