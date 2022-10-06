/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:19:09 by hoigag            #+#    #+#             */
/*   Updated: 2022/10/03 19:44:29 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	mem_size;

	mem_size = count * size;
	ptr = malloc(mem_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, mem_size);
	return (ptr);
}
