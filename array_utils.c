/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:55:58 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/30 13:40:45 by hoigag           ###   ########.fr       */
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
	new = ft_malloc(sizeof(char *) * (array_size(arr) + 2));
	if (!new)
		return (NULL);
	while (arr && arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	new[i] = ft_strdup(value);
	new[i + 1] = NULL;
	ft_free_2d(arr);
	return (new);
}

void	print_cmd_table(char **args)
{
	int	i;

	i = 0;
	if (!args || !args[0])
	{
		printf("cmd_table is empty\n");
		return ;
	}
	while (args[i])
	{
		printf("[%s]", args[i]);
		i++;
	}
	printf("\n");
}
// {
// 	int	i;

// 	i = 0;
// 	while (shell->cmd_table[i])
// 	{
// 		printf("[%s]", shell->cmd_table[i]);
// 		i++;
// 	}
// 	printf("\n");
// }
