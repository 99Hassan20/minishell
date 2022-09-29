/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:49:39 by hoigag            #+#    #+#             */
/*   Updated: 2022/09/29 12:58:04 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_isprint(int c)
{
    return (c >= 32 && c <= 126);
}