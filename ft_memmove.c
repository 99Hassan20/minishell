/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:26:26 by hoigag            #+#    #+#             */
/*   Updated: 2022/10/10 17:56:10 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char		*nsrc;
	unsigned char	*ndst;

	nsrc = src;
	ndst = dst;
	if (dst > src)
		while (len--)
			ndst[len] = nsrc[len];
	else
		ft_memcpy(dst, src, len);
	return (dst);
}




