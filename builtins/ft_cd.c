/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:20:47 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/02 17:35:17 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		g_exit_status = 1;
		return ;
	}
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		g_exit_status = 1;
	}
	else
	{
		getcwd(shell->cwd, sizeof(shell->cwd));
		// set_env(&shell->env, "PWD", shell->cwd, 1);
		g_exit_status = 0;
	}
}
