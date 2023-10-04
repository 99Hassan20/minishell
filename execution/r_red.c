/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_red.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ou <abdel-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 10:19:43 by abdel-ou          #+#    #+#             */
/*   Updated: 2023/09/30 12:43:42 by abdel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_of_rred(t_shell *shell, int i)
{
	int	frred;

	frred = open(shell->ready_commands[i].redirections->file,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (frred == -1)
	{
		error_log(shell->ready_commands[i].redirections->file);
		g_exit_status = 1;
		if (shell->ready_commands[i].cmd)
			exit(g_exit_status);
	}
	if (shell->ready_commands[i].cmd)
		dup2(frred, 1);
}

void	ft_rred(t_shell *shell, int i)
{
	int	frred;

	while (shell->ready_commands[i].redirections->next)
	{
		frred = open(shell->ready_commands[i].redirections->file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (frred == -1)
		{
			error_log(shell->ready_commands[i].redirections->file);
			g_exit_status = 1;
			exit (g_exit_status);
		}
		close(frred);
		if (shell->ready_commands[i].redirections->next->type == RRED)
			shell->ready_commands[i].redirections
				= shell->ready_commands[i].redirections->next;
		else
			break ;
	}
	end_of_rred(shell, i);
}

void	end_of_arred(t_shell *shell, int i)
{
	int	farred;

	farred = open(shell->ready_commands[i].redirections->file,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (farred == -1)
	{
		error_log(shell->ready_commands[i].redirections->file);
		g_exit_status = 1;
		if (shell->ready_commands[i].cmd)
			exit(g_exit_status);
	}
	if (shell->ready_commands[i].cmd)
		dup2(farred, 1);
}

void	ft_arred(t_shell *shell, int i)
{
	int	farred;

	while (shell->ready_commands[i].redirections->next)
	{
		farred = open(shell->ready_commands[i].redirections->file,
				O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (farred == -1)
		{
			error_log(shell->ready_commands[i].redirections->file);
			g_exit_status = 1;
			exit(g_exit_status);
		}
		if (shell->ready_commands[i].redirections->next->type == ARRED)
			shell->ready_commands[i].redirections
				= shell->ready_commands[i].redirections->next;
		else
			break ;
	}
	end_of_arred(shell, i);
}
