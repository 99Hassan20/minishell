# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/01 15:58:46 by hoigag            #+#    #+#              #
#    Updated: 2022/10/12 14:50:46 by hoigag           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS =-Wall -Wextra -Werror  
NAME = libft.a
SRCS = *.c
OBJS = $(SRCS:c=o)
BONUS_SRCS = $(wildcard ft_lst*.c)
BONUS_OBJS =  $(BONUS_SRCS:c=o)

all: $(NAME)

$(NAME): objects
	ar -rc $(NAME) $(OBJS)

bonus: $(NAME) $(BONUS_OBJS)
	ar -rc $(NAME) $(BONUS_OBJS)

:.o : $(SRCS) $(BONUS_SRCS) 
	$(cc) $(CFLAGS) -c $^
	
clean:
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all