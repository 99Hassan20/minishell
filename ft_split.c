/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:45:57 by hoigag            #+#    #+#             */
/*   Updated: 2022/10/18 13:27:52 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	counter;
	int	i;
	int	found;

	found = 0;
	counter = 0;
	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == c && found)
			{
				counter++;
				found = 0;
			}
			if (s[i] != c && !found)
				found = 1;
			i++;
		}
	}
	return (counter);
}

char	**ft_split(const char *s, char c)
{
	size_t		i;
	size_t		j;
	int			counter;
	char		**words;
	int			found;

	i = 0;
	j = 0;
	counter = 0;
	found = 0;
	words = (char **) malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!words)
		return (NULL);
	while (counter < count_words(s, c))
	{
		words[counter] = 
	}
	while (i <= ft_strlen(s))
	{
		if ((s[i] == c || s[i] == '\0') && found)
		{
			words[counter] = ft_substr(s, j, i - j);
			counter++;
			found = 0;
		}
		else if (s[i] != c && !found)
		{
			found = 1;
			j = i;
		}
		i++;
	}
	words[counter] = 0;
	return (words);
}

#include <stdio.h>
int main()
{
	char **words = ft_split(NULL, 'e');
	if (!words)
	{
		printf("NULL\n");
		return 0;
	}
	for(int i=0;words[i];i++)
	{
		printf("%s\n", words[i]);
	}
}

// int	word_count(char const *s, char c)
// {
// 	int	i;
// 	int	counter;

// 	i = 0;
// 	counter = 0;

// 	while (s[i])
// 	{
// 		if (s[i] == c && s[i - 1] != c)
// 			counter++;
// 		i++;
// 	}
// 	if (s[i] == '\0' && s[i - 1] != c)
// 		counter++;
// 	return (counter);
// }

// char	**ft_split(char const *s, char c)
// {
// 	int		i;
// 	char	**words;
// 	int		j;
// 	int		counter;

// 	counter = 0;
// 	j = 0;
// 	i = 0;
// 	words = malloc(sizeof(char *) * (word_count(s, c) + 1));
// 	if (!words)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		if (s[i] != c)
// 		{
// 			j = i;
// 			while (s[j] != c && s[j])
// 				j++;
// 			words[counter] = ft_substr(s, i, j - i);
// 			counter++;
// 			i = j;
// 		}
// 		i++;
// 	}
// 	words[counter] = 0;
// 	return (words);
// }
