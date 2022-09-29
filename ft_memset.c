/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:57:30 by hoigag            #+#    #+#             */
/*   Updated: 2022/09/29 19:05:51 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memset(void *b, int c, size_t len)
{
    int i = 0;
    char *p = (unsigned char *) b;
    while(*p)
    {
        if(i < len)
        {
            *p = (unsigned char) c;
        }
        p++;
        i++;
    }
    return b;
}