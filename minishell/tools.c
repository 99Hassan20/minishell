/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelmajid <abdelmajid@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 09:37:32 by abdelmajid        #+#    #+#             */
/*   Updated: 2023/09/10 13:21:26 by abdelmajid       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	ft_word_count(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (count);
}

static char	*ft_print_line(const char *s1, int *index, char c)
{
	char	*copy;
	size_t	word_len;
	int		i;

	word_len = 0;
	while (s1[*index] == c)
		(*index)++;
	i = *index;
	while (s1[i] && s1[i] != c)
	{
		word_len++;
		i++;
	}
	copy = malloc(sizeof(char) * (word_len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (s1[*index] && s1[*index] != c)
		copy[i++] = s1[(*index)++];
	copy[i] = '\0';
	return (copy);
}

static char	**free_err(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char	**ft_splitt(char const *s, char c)
{
	char	**arr;
	int		index;
	int		word_count;
	int		i;

	index = 0;
	i = 0;
	if (!s)
		return (NULL);
	word_count = ft_word_count(s, c);
	arr = malloc(sizeof(char *) * (word_count + 1));
	if (!arr)
		return (NULL);
	while (i < word_count)
	{
		arr[i] = ft_print_line(s, &index, c);
		if (!arr[i])
			return (free_err(arr));
		i++;
	}
	arr[i] = 0;
	return (arr);
}

char ***to3d_arr(char *str)
{
    char ***to_3d;
    int i = 0;
    char **pip_splite;
    pip_splite = ft_splitt(str, '|');
    while (pip_splite[i])
        i++;
    
    to_3d = malloc(sizeof(char **) * (i + 1) );
    i = 0;
    while (pip_splite[i])
    {
        to_3d[i] =  ft_splitt(pip_splite[i], ' ');
        i++;
    }
    to_3d[i] = NULL;
    return to_3d;
    
}