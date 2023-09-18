/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:34:01 by abdelmajid        #+#    #+#             */
/*   Updated: 2023/09/18 09:56:23 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_relative_path(char *file)
{
	if (!file)
		return (0);
	if ((file[0] == '.' && file[1] == '/')
		|| (file[0] == '.' && file[1] == '.' && file[1] == '/')
		|| file[0] == '/')
	{
		if (access(file, F_OK) != 0)
		{
			printf("minishell: %s: No such file or directory\n", file);
			g_exit_status = 127;
		}
		else if (access(file, X_OK) != 0)
		{
			printf("minishell: %s: Permission denied\n", file);
			g_exit_status = 126;
		}
		return (0);
	}
	return (1);
}

void	execute_parent_builtin(t_shell *shell, char **cmd)
{
	if (ft_strcmp(cmd[0], "cd") == 0 
		|| ((ft_strcmp(cmd[0], "export") == 0) && cmd[1])
		|| ((ft_strcmp(cmd[0], "unset") == 0) && cmd[1])
		|| ((ft_strcmp(cmd[0], "exit") == 0) && cmd[1]))
		execute_builtins(shell, cmd);
}

void	execline(t_shell *shell, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		fdd;	
	char	*executable;
	DIR		*dir;
	int		i = 0;

	fdd = 0;
	while (i < shell->cmd_count)
	{
		dir = opendir(shell->ready_commands[i].cmd);
		if (!is_builtin(shell->ready_commands[i].cmd) && dir)
		{
			closedir(dir);
			printf("minishell: %s: is a directory\n", shell->ready_commands[i].cmd);
			g_exit_status = 126;
			i++;
			continue ;
		}
		executable = get_full_path(shell->env, shell->ready_commands[i].args);
		if (!executable && !is_relative_path(shell->ready_commands[i].cmd))
		{
			i++;
			continue ;
		}
		if ((ft_strcmp(shell->ready_commands[i].cmd, "cd") == 0 && shell->cmd_count != 1))
		{
			i++;
			continue ;
		}
		if (((ft_strcmp(shell->ready_commands[i].cmd, "export") == 0) && shell->ready_commands[i].args[1]) 
			|| ((ft_strcmp(shell->ready_commands[i].cmd, "unset") == 0) && shell->ready_commands[i].args[1])
			|| ((ft_strcmp(shell->ready_commands[i].cmd, "exit") == 0))
			|| ((ft_strcmp(shell->ready_commands[i].cmd, "cd") == 0) && shell->cmd_count == 1))
		{
			execute_builtins(shell, shell->ready_commands[i].args);
			i++;
			continue ;
		}
		if (!is_builtin(shell->ready_commands[i].cmd) && !executable)
		{
			printf("minishell: %s: command not found\n", shell->ready_commands[i].cmd);
			g_exit_status = 127;
			i++;
			continue ;
		}
		pipe(fd);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
			dup2(fdd, 0);
			if (i + 1 < shell->cmd_count && shell->ready_commands[i + 1].args != NULL)
				dup2(fd[1], 1);
			// exit(125);
			close(fd[0]);
			if (is_child_builtin(shell->ready_commands[i].cmd))
				execute_builtins(shell, shell->ready_commands[i].args);
			else
				execve(executable, shell->ready_commands[i].args, env);
			exit(g_exit_status);
		}
		else
		{
			waitpid(pid, &g_exit_status, 0);
			close(fd[1]);
			fdd = fd[0];
			i++;
		}
	}
	g_exit_status %= 255;
}
