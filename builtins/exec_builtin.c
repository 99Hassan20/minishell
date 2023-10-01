/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ou <abdel-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:09:59 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/01 15:51:00 by abdel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	char	*builtins[9];
	int		i;

	if (!cmd)
		return (0);
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = "ENV";
	builtins[8] = NULL;
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(builtins[i], cmd) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_child_builtin(char *cmd)
{
	char	*builtins[5];
	int		i;

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
	{
		if (!command[1])
			print_env(shell->env, 2);
		else
			ft_export(shell, command);
	}
	else if (ft_strcmp(command[0], "unset") == 0)
		ft_unset(shell, command);
		
}
