/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:20:47 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/13 19:12:07 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_chdir(t_shell *shell, char **command)
{
	char	*path;

	if (!command[1])
		path = get_env(shell->env, "HOME");
	else
		path = command[1];
	if (!path)
	{
		printf("minishell: cd: HOME not set\n");
		shell->exit_status = 1;
		return ;
	}
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		shell->exit_status = 1;
	}
	else
	{
		getcwd(shell->cwd, sizeof(shell->cwd));
		set_env(&shell->env, "PWD", shell->cwd, 1);
		shell->exit_status = 0;
	}
}
