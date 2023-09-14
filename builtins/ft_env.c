/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:18:19 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/14 14:54:14 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_shell *shell, char **command)
{
	int	i;

	i = 1;
	while (command[i])
	{
		if (ft_strcmp(command[i], "env") != 0)
		{
			printf("env: %s: No such file or directory\n", command[i]);
			g_exit_status = 127;
			return ;
		}
		i++;
	}
	print_env(shell->env, 1);
	g_exit_status = 0;
}
