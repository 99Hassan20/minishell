// #include "libft.h"
#include <stdio.h>
#include "libft.h"
#include <ctype.h>
void is_alpha_test(int c)
{
    printf("isalpha test....\n");
    printf("mine : %d\n", ft_isalpha(c));
    printf("original : %d\n", isalpha(c));
    printf("isalpha test....\n");
}
void is_digit_test(int c)
{
    printf("isdigit test....\n");
    printf("mine : %d\n", ft_isdigit(c));
    printf("original : %d\n", isdigit(c));
    printf("isdigit test....\n");
}
void is_alnum_test(int c)
{
    printf("alnum test....\n");
    printf("mine : %d\n", ft_isalnum(c));
    printf("original : %d\n", isalnum(c));
    printf("alnum test....\n");
}


int main()
{      
    // is_alpha_test(5);
    //  is_digit_test('5');
    is_alnum_test('g');
    return 0;
}