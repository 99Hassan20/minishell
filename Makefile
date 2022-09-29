run: ft_*.c main.c libft.h
	gcc -Wall -Werror -Wextra ft_*.c main.c
clean:
	rm *.o
fclean: clean
	rm a.out