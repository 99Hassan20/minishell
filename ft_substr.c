/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:54:05 by hoigag            #+#    #+#             */
/*   Updated: 2022/10/05 15:17:31 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (NULL);
	substr = ft_calloc(sizeof(char), len + 1);
	if (!substr)
		return (NULL);
	if (start < ft_strlen(s))
		ft_memcpy(substr, s + start, len);
	return (substr);
}
