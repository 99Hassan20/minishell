/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ou <abdel-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:34:01 by abdelmajid        #+#    #+#             */
/*   Updated: 2023/09/19 16:00:05 by abdel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_relative_path(char *file)
{
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

void	red(t_shell *shell , int i)
{
	if (shell->ready_commands[i].redirections->type == RRED)
	{
		int frred = open(shell->ready_commands[i].redirections->file ,O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(frred, 1);
	}
	if (shell->ready_commands[i].redirections->type == ARRED)
	{
		int farred = open(shell->ready_commands[i].redirections->file, O_APPEND | O_WRONLY | O_CREAT, 0644);
		dup2(farred, 1);
	}
	
}

void	execline(t_shell *shell, char ***cmd, char **env)
{
	int		fd[2];
	pid_t	*pid;
	int		i = 0;
	int		fdd;	
	char	*executable;
	DIR		*dir;

	fdd = 0;
	while (*cmd)
	{
		dir = opendir((*cmd)[0]);
		pid = (pid_t *)malloc(sizeof(pid_t) * shell->cmd_count);
		if (!is_builtin(*cmd[0]) && dir)
		{
			closedir(dir);
			printf("minishell: %s: is a directory\n", (*cmd)[0]);
			g_exit_status = 126;
			cmd++;
			continue ;
		}
		executable = get_full_path(shell->env, *cmd);
		if (!executable && !is_relative_path((*cmd)[0]))
		{
			cmd++;
			continue ;
		}
		if ((ft_strcmp((*cmd)[0], "cd") == 0 && shell->cmd_count != 1))
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
		fd[1] = dup(0);
    	fd[0] = dup(1);
		pipe(fd);
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid[i] == 0)
		{
			dup2(fdd, 0);
			if (*(cmd + 1) != NULL)
			{
				
				dup2(fd[1], 1);
				
			}
			close(fd[0]);
	
			if (is_child_builtin(*cmd[0]))
				execute_builtins(shell, *cmd);
			else
			{
				if (!shell->ready_commands[i].redirections)
				{
					execve(executable, *cmd, env);
				}
					red(shell ,i);
					execve(executable, *cmd, env);
				if (shell->ready_commands[i].redirections->type == LRED)
				{
					int flred = open(shell->ready_commands[i].redirections->file ,O_RDONLY, 0644);
					if (flred == -1)
					{
						printf("%s: No such file or directory \n",shell->ready_commands[i].redirections->file);
						exit(g_exit_status);
					}
					else
					{
					dup2(flred,0);
					execve(executable, *cmd, env);
					}
					
					







	
				}
				
			}	
			exit(g_exit_status);
		}
		else
		{
			// printf("\n %d pid = %d \n",i,pid[i]);
// waitpid(pid[i], &g_exit_status, 0);
			close(fd[1]);
			fdd = fd[0];
			cmd++;
			i++;
		}
	}
	while(wait(&g_exit_status) > 0);
		
	g_exit_status %= 255;
}
