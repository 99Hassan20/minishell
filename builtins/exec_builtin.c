/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:09:59 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/13 11:19:07 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_builtin(char *cmd)
{
	char *builtins[8];
	int i = 0;

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	while (builtins[i])
	{
		if (ft_strcmp(builtins[i], cmd) == 0)
			return (1);
		i++;
	}
	return (0);
}

int is_child_builtin(char *cmd)
{
	char *builtins[5];
	int  i;

	i = 0;
	builtins[0] = "echo";
	builtins[1] = "pwd";
	builtins[2] = "env";
	builtins[3] = "export";
	builtins[4] = NULL;
	while (builtins[i])
	{
		if (ft_strcmp(builtins[i], cmd) == 0)
			return (1);
		i++;
	}
	return (0);
}


// void	execute_builtins(t_shell *shell, t_command command)
// {
// 	if (ft_strcmp(command.cmd, "env") == 0)
// 		ft_env(shell, command);
// 	else if (ft_strcmp(command.cmd, "echo") == 0)
// 		ft_echo(shell, command);
// 	else if (ft_strcmp(command.cmd, "pwd") == 0)
// 		ft_pwd(shell);
// 	else if (ft_strcmp(command.cmd, "cd") == 0)
// 		ft_chdir(shell, command);
// 	else if (ft_strcmp(command.cmd, "export") == 0)
// 		ft_export(shell, command);
// 	else if (ft_strcmp(command.cmd, "exit") == 0)
// 		ft_exit(shell, command);
// 	else if (ft_strcmp(command.cmd, "unset") == 0)
// 		ft_unset(shell, command);
// }

void	execute_builtins(t_shell *shell, char **command)
{
	if (ft_strcmp(command[0], "env") == 0)
		ft_env(shell, command);
	else if (ft_strcmp(command[0], "echo") == 0)
		ft_echo(shell, command);
	else if (ft_strcmp(command[0], "pwd") == 0)
		ft_pwd(shell);
	else if (ft_strcmp(command[0], "cd") == 0)
		ft_chdir(shell, command);
	else if (ft_strcmp(command[0], "exit") == 0)
		ft_exit(shell, command);
	else if (ft_strcmp(command[0], "export") == 0)
		ft_export(shell, command);
	else if (ft_strcmp(command[0], "unset") == 0)
		ft_unset(shell, command);
}
