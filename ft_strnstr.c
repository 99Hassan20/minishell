/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:55:20 by hoigag            #+#    #+#             */
/*   Updated: 2022/10/03 18:18:39 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!needle || ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (haystack[i])
	{
		if (haystack[i] == needle[j])
		{
			while (i + j < len && needle[j] && haystack[i + j] == needle[j])
				j++;
			if (j == ft_strlen(needle))
				return ((char *)(haystack + i));
			j = 0;
		}
		i++;
	}
	return (NULL);
}
