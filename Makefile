# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/01 15:58:46 by hoigag            #+#    #+#              #
#    Updated: 2022/10/04 19:35:20 by hoigag           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



CC = gcc
CFLAGS =-Wall -Wextra -Werror  
SRCS = $(wildcard *.c)
OBJS = $(SRCS:c=o)
NAME = libft.a



all: $(NAME)


$(NAME): objects
	ar -rc $(NAME) $(OBJS)

objects: $(SRCS)
	$(CC) $(CFLAGS) -c $^ 

# main.o: main.c
# 	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf $(wildcard *.o)

fclean: clean
	rm -rf $(NAME)

re: fclean all