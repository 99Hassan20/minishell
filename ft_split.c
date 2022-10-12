/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:45:57 by hoigag            #+#    #+#             */
/*   Updated: 2022/10/11 21:29:23 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	word_count(char const *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			counter++;
		i++;
	}
	if (s[i] == '\0' && s[i - 1] != c)
		counter++;
	return (counter);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**words;
	int		j;
	int		counter;

	counter = 0;
	j = 0;
	i = 0;
	words = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!words)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			j = i;
			while (s[j] != c && s[j])
				j++;
			words[counter] = ft_substr(s, i, j - i);
			counter++;
			i = j;
		}
		i++;
	}
	words[counter] = 0;
	return (words);
}