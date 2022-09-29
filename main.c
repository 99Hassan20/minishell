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
void is_ascii_test(int c)
{
    printf("isascii test....\n");
    printf("mine : %d\n", ft_isascii(c));
    printf("original : %d\n", isascii(c));
    printf("isascii test....\n");
}
void is_print_test(int c)
{
    printf("isprint test....\n");
    printf("mine : %d\n", ft_isprint(c));
    printf("original : %d\n", isprint(c));
    printf("isprint test....\n");
}
void strlen_test(const char *s)
{
    printf("strlen test\n");
    printf("mine : %zu\n", ft_strlen(s));
    printf("original : %lu\n", strlen(s));
    printf("strlen end");
}
void toupper_test(int c)
{
    printf("toupper test\n");
    printf("mine: %c\n", ft_toupper(c));
    printf("theirs: %c\n", toupper(c));
    printf("end of test");
}
void tolower_test(int c)
{
    printf("tolower test\n");
    printf("mine: %c\n", ft_tolower(c));
    printf("theirs: %c\n", tolower(c));
    printf("end of test");
}

void ft_strchr_test(const char *s, int c)
{
    printf("strchr test....\n");
    printf("mine : %c\n", *ft_strchr(s, c));
    printf("theirs : %c\n", *strchr(s, c));
    printf("strchr test end....\n");
}

int main()
{      
    // is_alpha_test(5);
    // is_digit_test('g');
    // is_alnum_test('g');
    // is_ascii_test(' ');
    // is_print_test(31);
    // strlen_test"");
    // toupper_test('z');
    // tolower_test('.');
    // ft_strchr_test("hassan", '5');
    return 0;
}