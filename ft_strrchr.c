/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:21:41 by hoigag            #+#    #+#             */
/*   Updated: 2022/09/29 18:42:21 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strrchr(const char *s, int c)
{
    int size = ft_strlen(s);
    char *p = ((char *) s) + size;
    while(size >= 0)
    {
        if (*p == c)
            return p;
        size--;
        p--;
    }
    return NULL;
}