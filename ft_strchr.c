/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:54:35 by hoigag            #+#    #+#             */
/*   Updated: 2022/09/29 15:24:05 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strchr(const char *s, int c)
{
    char *i = (char *) s;
    while(*i)
    {
        if (*i == (char) c)
            return i;
        i++;
    }
    if (*i == (char) c)
        return i;
    return NULL;
}

