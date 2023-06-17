/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:18:19 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/17 13:35:47 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_shell *shell)
{
	int	i;

	i = 1;
	while (shell->cmd_table[i])
	{
		if (ft_strcmp(shell->cmd_table[i], "env") != 0)
		{
			printf("env: %s: No such file or directory\n", shell->cmd_table[i]);
			shell->exit_status = 127;
			return ;
		}
		i++;
	}
	print_env(shell->env, 1);
	shell->exit_status = 0;
}
