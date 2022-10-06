/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:52:03 by hoigag            #+#    #+#             */
/*   Updated: 2022/10/06 13:04:40 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int char_in_set(const char *set, char c)
{
    int i;

    i = 0;
    while (set[i])
    {
        if (set[i] == c)
            return (1);
        i++;
    }
    return (0);
}

char *ft_strtrim(char const *s1, char const *set)
{
	int	i = 0;
	int j = ft_strlen(s1) - 1;
	while (s1[i])
	{
		if (!char_in_set(set, s1[i]))
			break ;
		i++;
	}
	while(j >= i)
	{
		if (!char_in_set(set, s1[j]))
			break ;
		j--;
	}
	int size = j - i + 1;
	return (ft_substr(s1, i, size));
}
