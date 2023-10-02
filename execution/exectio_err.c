/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exectio_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ou <abdel-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:11:56 by abdel-ou          #+#    #+#             */
/*   Updated: 2023/10/02 19:01:25 by abdel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_log(char *file_name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file_name, 2);
	if (access(file_name, F_OK) != 0)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": Permission denied\n", 2);
}

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

int	ft_check_dir(t_shell *shell, int *i)
{
	DIR		*dir;

	dir = opendir(shell->ready_commands[*i].cmd);
	if (!is_builtin(shell->ready_commands[*i].cmd) && dir)
	{
		closedir(dir);
		printf("minishell: %s: is a directory\n", shell->ready_commands[*i].cmd);
		g_exit_status = 126;
		(*i)++;
		return (0);
	}
	if (dir)
		closedir(dir);
	return (1);
}
