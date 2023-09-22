/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ou <abdel-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:34:01 by abdelmajid        #+#    #+#             */
/*   Updated: 2023/09/22 13:07:53 by abdel-ou         ###   ########.fr       */
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

void	redirection(t_shell *shell , int i)
{
	if (shell->ready_commands[i].redirections->type == RRED)
	{
				int frred; 
		while (shell->ready_commands[i].redirections->next)
		{
			frred = open(shell->ready_commands[i].redirections->file ,O_WRONLY | O_CREAT | O_TRUNC, 0644);
			close(frred);
			shell->ready_commands[i].redirections = shell->ready_commands[i].redirections->next;
		}
		frred = open(shell->ready_commands[i].redirections->file ,O_WRONLY | O_CREAT | O_TRUNC, 0644);
		
		dup2(frred, 1);
	}

	
	if (shell->ready_commands[i].redirections->type == ARRED)
	{
		int farred; 
		while (shell->ready_commands[i].redirections->next)
		{
			farred = open(shell->ready_commands[i].redirections->file, O_APPEND | O_WRONLY | O_CREAT, 0644);;
			close(farred);
			shell->ready_commands[i].redirections = shell->ready_commands[i].redirections->next;
		}
		farred = open(shell->ready_commands[i].redirections->file, O_APPEND | O_WRONLY | O_CREAT, 0644);
		
		dup2(farred, 1);
		
	
	}

		// int farred = open(shell->ready_commands[i].redirections->file, O_APPEND | O_WRONLY | O_CREAT, 0644);

	
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
		}	
	}
}

void	herdocs(t_shell *shell, int i)
{
	char *delimiter;
	int tmp1 = open("/tmp/tmpp" ,O_WRONLY | O_CREAT | O_TRUNC, 0777);
	rl_catch_signals = 1;
	while (1)
	{
		delimiter = readline("> ");
		if (ft_strcmp(shell->ready_commands[i].herdocs->file,delimiter) == 0)
			break;
		if (delimiter[0] == '$' && (delimiter + 1))
			ft_putstr_fd(get_env(shell->env, delimiter + 1),tmp1);
		else
		{
			ft_putstr_fd(delimiter,tmp1);
			ft_putchar_fd('\n',tmp1);
		}
	}
	// open(0, O_RDONLY);
	close(tmp1);
	int tmp2 = open("/tmp/tmpp",O_RDONLY);
	unlink("/tmp/tmpp");
	dup2(tmp2,0);
	// printf("hello herdoc  %s \n",shell->ready_commands[i].herdocs->file);
	close(tmp2);
	shell->ready_commands[i].herdocs = shell->ready_commands[i].herdocs->next;
	rl_catch_signals = 0;
}

void	execline(t_shell *shell, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		i = 0;
	int		fdd;	
	char	*executable;
	DIR		*dir;
	int		iter = 0;

	fdd = 0;
	// 
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
		if (!executable && !is_relative_path(shell->ready_commands[i].cmd) && shell->ready_commands[i].herdocs)
		{
			char *lol[2];
			lol[0] = "cat";
			lol[1] = NULL;
			int fd;

			fd = fork();
			if (fd < 0)
				exit(255);
			else if (fd == 0)
			{
				herdocs(shell,i);
				execve("/bin/cat", lol, env);	
			}
			else
				waitpid(fd, &g_exit_status, 0);
			i++;
			continue;
		}
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
		if (!is_builtin(shell->ready_commands[i].cmd) && !executable )
		{
			printf("minishell: %s: command not found\n", shell->ready_commands[i].cmd);
			g_exit_status = 127;
			i++;
			continue ;
		}

		if ((i + 1) < shell->cmd_count)
				pipe(fd);	
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
			close(fd[0]);
			dup2(fdd, 0);
			if (i + 1 < shell->cmd_count)
			{
				dup2(fd[1], 1);
				close(fd[1]);
			}
				
			if(shell->ready_commands[i].herdocs && shell->ready_commands[i].cmd )
			{
				herdocs(shell,i);
				execve(executable, shell->ready_commands[i].args, env);
			}
			
		if (is_child_builtin(shell->ready_commands->cmd))
				execute_builtins(shell,	shell->ready_commands[i].args);

		if (!shell->ready_commands[i].redirections && !shell->ready_commands[i].herdocs 
			&& !is_child_builtin(shell->ready_commands->cmd))
					execve(executable, shell->ready_commands[i].args, env);
				
		if (shell->ready_commands[i].redirections)
			{
				redirection(shell ,i);
				execve(executable, shell->ready_commands[i].args, env);
			}

			exit(g_exit_status);
		}
		else
		{
			if (i + 1 == shell->cmd_count)
				waitpid(pid, &g_exit_status, 0);
			if (fdd)
				close(fdd);
			
		if (i + 1 < shell->cmd_count)
				fdd = dup(fd[0]);	
			close(fd[1]);
			close(fd[0]);
		}
		iter++;
		i++;
	}
	
	while (wait(NULL) > 0);
	
	g_exit_status %= 255;
}
