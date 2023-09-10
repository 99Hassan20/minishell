/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelmajid <abdelmajid@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:34:01 by abdelmajid        #+#    #+#             */
/*   Updated: 2023/09/10 13:59:51 by abdelmajid       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execline(char ***cmd, char **env)
{
	int fd[2];
    int status;
	pid_t pid;
	int fdd = 0;				/* Backup */

	while (*cmd != NULL) {
		pipe(fd);				/* Sharing bidiflow */
		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
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
			waitpid(pid, &status, 0); 		/* Collect childs */
			close(fd[1]);
			fdd = fd[0];
			cmd++;
		}
	}
}


