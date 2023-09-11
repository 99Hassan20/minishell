/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:24:44 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/11 12:24:45 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_exit_status(char *status)
{
	int		i;
	char	*trimmed;

	trimmed = ft_strtrim(status, "\t\r ");
	i = 0;
	if (trimmed[0] == '-' || trimmed[0] == '+')
		i++;
	while (trimmed[i])
	{
		if (!ft_isdigit(trimmed[i]))
			return (0);
		i++;
	}
	free(trimmed);
	return (1);
}

void	ft_exit(t_shell *shell, char **command)
{
	if (!command[1])
		exit(shell->exit_status);
	if (!is_valid_exit_status(command[1]))
	{
		shell->exit_status = 255;
		printf("bash: exit: \
%s: numeric argument required\n", command[1]);
	}
	else if (command[2])
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		shell->exit_status = 1;
		return ;
	}
	else
		shell->exit_status = ft_atoi(command[1]);
	exit(shell->exit_status);
}

// void	ft_exit(t_shell *shell, t_command command)
// {
// 	if (!command.args[1])
// 		exit(shell->exit_status);
// 	if (!is_valid_exit_status(command.args[1]))
// 	{
// 		shell->exit_status = 255;
// 		printf("bash: exit: \
// %s: numeric argument required\n", command.args[1]);
// 	}
// 	else if (command.args[2])
// 	{
// 		printf("exit\n");
// 		printf("minishell: exit: too many arguments\n");
// 		shell->exit_status = 1;
// 		return ;
// 	}
// 	else
// 		shell->exit_status = ft_atoi(command.args[1]);
// 	exit(shell->exit_status);
// }