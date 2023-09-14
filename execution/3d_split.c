/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:34:01 by abdelmajid        #+#    #+#             */
/*   Updated: 2023/09/14 14:54:14 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_parent_builtin(t_shell *shell, char **cmd)
{
	if (ft_strcmp(cmd[0], "cd") == 0 
		|| ((ft_strcmp(cmd[0], "export") == 0) && cmd[1])
		|| ((ft_strcmp(cmd[0], "unset") == 0) && cmd[1])
		|| ((ft_strcmp(cmd[0], "exit") == 0) && cmd[1]))
		execute_builtins(shell, cmd);
}

void	execline(t_shell *shell, char ***cmd, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		fdd;	
	char	*executable;

	fdd = 0;
	while (*cmd)
	{
		executable = get_full_path(shell->env, *cmd);
		if (ft_strcmp((*cmd)[0], "cd") == 0 && shell->cmd_count != 1)
		{
			cmd++;
			continue ;
		}
		if (((ft_strcmp((*cmd)[0], "export") == 0) && cmd[0][1]) 
			|| ((ft_strcmp((*cmd)[0], "unset") == 0) && cmd[0][1])
			|| ((ft_strcmp((*cmd)[0], "exit") == 0))
			|| ((ft_strcmp((*cmd)[0], "cd") == 0) && shell->cmd_count == 1))
		{
			execute_builtins(shell, *cmd);
			cmd++;
			continue ;
		}
		if (!is_builtin(*cmd[0]) && !executable)
		{
			printf("minishell: %s: command not found\n", *cmd[0]);
			g_exit_status = 127;
			cmd++;
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
			if (*(cmd + 1) != NULL)
				dup2(fd[1], 1);
			close(fd[0]);
			if (is_child_builtin(*cmd[0]))
				execute_builtins(shell, *cmd);
			else
				execve(executable, *cmd, env);
			exit(g_exit_status);
		}
		else
		{
			waitpid(pid, &g_exit_status, 0);
			close(fd[1]);
			fdd = fd[0];
			cmd++;
		}
	}
	g_exit_status %= 255;
}
