/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whiout_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ou <abdel-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:20:35 by abdel-ou          #+#    #+#             */
/*   Updated: 2023/09/30 15:42:00 by abdel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	norminet_helper(t_shell *shell, int *i, char *executable)
{
	if (!is_builtin(shell->ready_commands[*i].cmd) && !executable)
	{
		printf("minishell: %s: command not found\n",
			shell->ready_commands[*i].cmd);
		g_exit_status = 127;
		(*i)++;
		return (0);
	}
	return (1);
}

int	run_redi_whiout_cmd(t_shell *shell, int *i)
{
	shell->executable = get_full_path(shell->env, shell->ready_commands[*i].args);
	if (!shell->executable && !is_relative_path(shell->ready_commands[*i].cmd))
	{
		if (shell->ready_commands[*i].herdocs)
			herdocs(shell,*i);
		if (shell->ready_commands[*i].redirections)
			redirection(shell, *i);
		(*i)++;
		return (0);
	}
	return (1);
}

int	ft_check_builtins_run(t_shell *shell, int *i)
{
	char	*executable;

	executable = get_full_path(shell->env, shell->ready_commands[*i].args);
	if ((ft_strcmp(shell->ready_commands[*i].cmd, "cd") == 0 
			&& shell->cmd_count != 1))
	{
		(*i)++;
		return (0);
	}
	if (((ft_strcmp(shell->ready_commands[*i].cmd, "export") == 0) 
			&& shell->ready_commands[*i].args[1]) 
		|| ((ft_strcmp(shell->ready_commands[*i].cmd, "unset") == 0) 
			&& shell->ready_commands[*i].args[1])
		|| ((ft_strcmp(shell->ready_commands[*i].cmd, "exit") == 0))
		|| ((ft_strcmp(shell->ready_commands[*i].cmd, "cd") == 0)
			&& shell->cmd_count == 1))
	{
		execute_builtins(shell, shell->ready_commands[*i].args);
		(*i)++;
		return (0);
	}
	if (norminet_helper(shell, i, executable) == 0)
		return (0);
	
	return (1);
}
