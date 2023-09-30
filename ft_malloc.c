#include "includes/minishell.h"

void *ft_malloc(size_t size)
{
    void *ptr;

    ptr = malloc(size);
    if (!ptr)
    {
        printf("Error: malloc failed\n");
        exit(1);
    }
    static int i;
    printf("malloc %d: %p\n", i++, ptr);
    return (ptr);
}