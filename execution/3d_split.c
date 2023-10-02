/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ou <abdel-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:21:28 by abdel-ou          #+#    #+#             */
/*   Updated: 2023/10/02 13:01:11 by abdel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_child(t_shell *shell, t_file_dis *file, int *i, char	__attribute__((unused))**env)
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
	if (shell->ready_commands[*i].herdocs
		&& shell->ready_commands[*i].cmd && !herdocs(shell, *i))
		return (0);
	if (shell->ready_commands[*i].redirections)
		redirection(shell, *i);
	if (!is_child_builtin(shell->ready_commands[*i].cmd))
	{
		char **env = env_to_array(shell->env);
		execve(executable, shell->ready_commands[*i].args, env);
	}
	if (is_child_builtin(shell->ready_commands[*i].cmd))
		execute_builtins(shell, shell->ready_commands[*i].args);
	if (executable)
		free(executable);
	exit(g_exit_status);
}

void	wait_pid(t_shell *shell, int *i, pid_t pid, t_file_dis *file)
{
	int	child_status;

	if ((*i) + 1 == shell->cmd_count)
		waitpid(pid, &child_status, 0);
	if (file->fdd)
		close(file->fdd);
	if ((*i) + 1 < shell->cmd_count)
	{
		file->fdd = dup(file->fd[0]);
		close(file->fd[1]);
		close(file->fd[0]);
	}
	if (WIFEXITED(child_status))
		g_exit_status = WEXITSTATUS(child_status);
	else if (WIFSIGNALED(child_status))
		g_exit_status = 128 + WTERMSIG(child_status);
}

int	ft_pipes(t_shell *shell, t_file_dis *file, int *i, char __attribute__((unused))**env)
{
	pid_t	pid;

	if ((*i + 1) < shell->cmd_count)
		pipe(file->fd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (0);
	}
	else if (pid == 0)
		return (if_child(shell, file, i, env));
	else
		wait_pid(shell, i, pid, file);
	return (1);
}

void	execline(t_shell *shell, char **env)
{
	int			i;
	t_file_dis	file;

	file.fdd = 0;
	i = 0;
	while (i < shell->cmd_count)
	{
		if (ft_check_dir(shell, &i) == 0)
			continue ;
		if (run_redi_whiout_cmd(shell, &i) == 0)
			continue ;
		if (ft_check_builtins_run(shell, &i) == 0)
			continue ;
		if (!ft_pipes(shell, &file, &i, env))
			return ;
		i++;
	}
	while (wait(NULL) > 0)
		;
	g_exit_status %= 255;
	// env_to_list(shell, env);
	ft_free_2d(env);
}
