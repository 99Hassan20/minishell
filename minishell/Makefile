# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdelmajid <abdelmajid@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/02 09:12:59 by abdelmajid        #+#    #+#              #
#    Updated: 2023/09/10 13:44:41 by abdelmajid       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =  main.c get_path.c tools.c 3d_split.c

CC = cc

FLAGS = -lreadline -Wall -Wextra -Werror


OBJ = $(SRC:.c=.o)


$(NAME) : $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)


%.o:%.c
	$(CC) $(FLAGS) -c $^ -o $@

all : $(NAME)

fclean:
	@rm -rf $(NAME) $(OBJ)
clean:
	@rm -rf $(OBJ)

re:fclean all 