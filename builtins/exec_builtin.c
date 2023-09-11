/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:09:59 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/11 09:51:17 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_builtins2(t_shell *shell, t_command command)
{
	if (ft_strcmp(command.cmd, "env") == 0)
		ft_env(shell, command);
	else if (ft_strcmp(command.cmd, "echo") == 0)
		ft_echo(shell, command);
	else if (ft_strcmp(command.cmd, "pwd") == 0)
		ft_pwd(shell);
	else if (ft_strcmp(command.cmd, "cd") == 0)
		ft_chdir(shell, command);
	else if (ft_strcmp(command.cmd, "export") == 0)
		ft_export(shell, command);
	else if (ft_strcmp(command.cmd, "exit") == 0)
		ft_exit(shell, command);
	else if (ft_strcmp(command.cmd, "unset") == 0)
		ft_unset(shell, command);
}

// void	execute_builtins(t_shell *shell)
// {
// 	if (ft_strcmp(shell->cmd_table[0], "env") == 0)
// 		ft_env(shell);
// 	else if (ft_strcmp(shell->cmd_table[0], "echo") == 0)
// 		ft_echo(shell);
// 	else if (ft_strcmp(shell->cmd_table[0], "pwd") == 0)
// 		ft_pwd(shell);
// 	else if (ft_strcmp(shell->cmd_table[0], "cd") == 0)
// 		ft_chdir(shell);
// 	else if (ft_strcmp(shell->cmd_table[0], "exit") == 0)
// 		ft_exit(shell);
// 	else if (ft_strcmp(shell->cmd_table[0], "export") == 0)
// 		ft_export(shell);
// 	else if (ft_strcmp(shell->cmd_table[0], "unset") == 0)
// 		ft_unset(shell);
// }
