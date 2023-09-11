/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:18:19 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/11 12:27:19 by hoigag           ###   ########.fr       */
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
			shell->exit_status = 127;
			return ;
		}
		i++;
	}
	print_env(shell->env, 1);
	shell->exit_status = 0;
}

// void	ft_env(t_shell *shell, t_command command)
// {
// 	int	i;

// 	i = 1;
// 	while (command.args[i])
// 	{
// 		if (ft_strcmp(command.args[i], "env") != 0)
// 		{
// 			printf("env: %s: No such file or directory\n", command.args[i]);
// 			shell->exit_status = 127;
// 			return ;
// 		}
// 		i++;
// 	}
// 	print_env(shell->env, 1);
// 	shell->exit_status = 0;
// }
