/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:26:26 by hoigag            #+#    #+#             */
/*   Updated: 2022/10/06 16:39:11 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	buffer[len];
	size_t			i;

	i = 0;
	while (i < len)
	{
		buffer[i] = ((unsigned char *) src)[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		((unsigned char *)dst)[i] = buffer[i];
		i++;
	}
	return (dst);
}
