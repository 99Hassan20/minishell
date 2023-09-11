/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:34:01 by abdelmajid        #+#    #+#             */
/*   Updated: 2023/09/11 15:26:49 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execline(t_shell *shell, char ***cmd, char **env)
{
	int fd[2];
	pid_t pid;
	int fdd = 0;	

	while (*cmd != NULL) {
		if (!is_child_builtin(*cmd[0]) && is_builtin(*cmd[0]))
		{
			execute_builtins(shell, *cmd);
			// printf("parent builtins\n");
			cmd++;
			continue ;
		}
		if (!getCommandPath(*cmd[0]))
		{
			printf("minishell: %s: command not found\n", *cmd[0]);
			shell->exit_status = 127;
			cmd++;
			continue ;
		}
		pipe(fd);
		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0 && is_child_builtin(*cmd[0]))
		{
			dup2(fdd, 0);
			if (*(cmd + 1) != NULL) {
				dup2(fd[1], 1);
			}
			close(fd[0]);
			execute_builtins(shell, *cmd);
			// printf("%d\n", shell->exit_status);
			exit(shell->exit_status);
		}
		else if (pid == 0) {
			dup2(fdd, 0);
			if (*(cmd + 1) != NULL) {
				dup2(fd[1], 1);
			}
			close(fd[0]);
			// execvp((*cmd)[0], *cmd);
            execve(getCommandPath(*cmd[0]), *cmd, env);
			exit(1);
		}
		else {
			waitpid(pid, &shell->exit_status, 0); 		/* Collect childs */
			close(fd[1]);
			fdd = fd[0];
			cmd++;
		}
	}
}


