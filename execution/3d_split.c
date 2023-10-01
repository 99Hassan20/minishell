/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ou <abdel-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:21:28 by abdel-ou          #+#    #+#             */
/*   Updated: 2023/10/01 08:59:34 by abdel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_chaild(t_shell *shell, file_dis *file, int *i, char	**env)
{
	char	*executable;

	executable = get_full_path(shell->env, shell->ready_commands[*i].args);
	if (file->fd[0])
		close(file->fd[0]);
	dup2(file->fdd, 0);
	if ((*i) + 1 < shell->cmd_count)
	{
		dup2(file->fd[1], 1);
		close(file->fd[1]);
	}
	if (shell->ready_commands[*i].herdocs && shell->ready_commands[*i].cmd)
		herdocs(shell, *i);
	if (shell->ready_commands[*i].redirections)
		redirection(shell, *i);
	if (!is_child_builtin(shell->ready_commands[*i].cmd))
		execve(executable, shell->ready_commands[*i].args, env);
	if (is_child_builtin(shell->ready_commands[*i].cmd))
		execute_builtins(shell, shell->ready_commands[*i].args);
	exit(g_exit_status);
}

void	wait_pid(t_shell *shell, int *i, pid_t pid, file_dis *file)
{
	if ((*i) + 1 == shell->cmd_count)
		waitpid(pid, &g_exit_status, 0);
	if (file->fdd)
		close(file->fdd);
	if ((*i) + 1 < shell->cmd_count)
	{
		file->fdd = dup(file->fd[0]);
		close(file->fd[1]);
		close(file->fd[0]);
	}
}

void	ft_pipes(t_shell *shell, file_dis *file, int *i, char **env)
{
	pid_t	pid;

	if ((*i + 1) < shell->cmd_count)
		pipe(file->fd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
		if_chaild(shell, file, i, env);
	else
		wait_pid(shell, i, pid, file);
}

void	execline(t_shell *shell, char **env)
{
	int			i;
	file_dis	file;

	file.fdd = 0;
	i = 0;
	while (i < shell->cmd_count)
	{
		if (ft_check_dir(shell, i) == 0)
			continue ;
		if (run_redi_whiout_cmd(shell, &i) == 0)
			continue ;
		if (ft_check_builtins_run(shell, &i) == 0)
			continue ;
		ft_pipes(shell, &file, &i, env);
		i++;
	}
	while (wait(NULL) > 0)
		;
	g_exit_status %= 255;
}
