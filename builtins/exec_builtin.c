/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:09:59 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/17 15:11:53 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_builtins(t_shell *shell)
{
	if (ft_strcmp(shell->cmd_table[0], "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(shell->cmd_table[0], "echo") == 0)
		ft_echo(shell);
	else if (ft_strcmp(shell->cmd_table[0], "pwd") == 0)
		ft_pwd(shell);
	else if (ft_strcmp(shell->cmd_table[0], "cd") == 0)
		ft_chdir(shell);
	else if (ft_strcmp(shell->cmd_table[0], "exit") == 0)
		ft_exit(shell);
	else if (ft_strcmp(shell->cmd_table[0], "export") == 0)
		ft_export(shell);
	else if (ft_strcmp(shell->cmd_table[0], "unset") == 0)
		ft_unset(shell);
}
