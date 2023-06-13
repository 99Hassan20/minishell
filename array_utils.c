/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:55:58 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/11 12:08:32 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	array_size(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

char	**append_to_array(char **arr, char *value)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (array_size(arr) + 2));
	if (!new)
		return (NULL);
	while (arr && arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	new[i] = value;
	new[i + 1] = NULL;
	ft_free_2d(arr);
	return (new);
}

void	print_cmd_table(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->cmd_table[i])
	{
		printf("[%s]", shell->cmd_table[i]);
		i++;
	}
	printf("\n");
}