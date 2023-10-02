/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_red.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 12:41:48 by abdel-ou          #+#    #+#             */
/*   Updated: 2023/10/02 18:10:09 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_of_lred(t_shell *shell, int i)
{
	int	flred;

	flred = open(shell->ready_commands[i].redirections->file,
			O_RDONLY, 0644);
	if (flred == -1)
	{
		error_log(shell->ready_commands[i].redirections->file);
		g_exit_status = 1;
		if (shell->ready_commands[i].cmd)
			exit(g_exit_status);
	}
	else
	{
		if (shell->ready_commands[i].cmd)
			dup2(flred, 0);
	}
}

void	ft_lred(t_shell *shell, int i)
{
	int	flred;

	while (shell->ready_commands[i].redirections->next)
	{
		flred = open(shell->ready_commands[i].redirections->file,
				O_RDONLY, 0644);
		if (flred == -1)
		{
			error_log(shell->ready_commands[i].redirections->file);
			g_exit_status = 1;
			exit(g_exit_status);
		}
		if (shell->ready_commands[i].redirections->next->type == LRED)
			shell->ready_commands[i].redirections
				= shell->ready_commands[i].redirections->next;
		else
			break ;
	}
	end_of_lred(shell, i);
}

void	redirection(t_shell *shell, int i)
{
	if (shell->ready_commands[i].redirections->type == RRED)
		ft_rred(shell, i);
	if (shell->ready_commands[i].redirections->type == ARRED)
		ft_arred(shell, i);
	if (shell->ready_commands[i].redirections->type == LRED)
		ft_lred(shell, i);
	shell->ready_commands[i].redirections
		= shell->ready_commands[i].redirections->next;
	if (shell->ready_commands[i].redirections)
		redirection(shell, i);
	// free(shell->ready_commands[i].redirections->file);
	// free(shell->ready_commands[i].redirections);
}
