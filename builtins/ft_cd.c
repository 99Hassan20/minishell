/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:20:47 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/17 13:36:47 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_chdir(t_shell *shell)
{
	char	*path;
	char	*old;

	old = ft_strdup(shell->cwd);
	if (!shell->cmd_table[1])
		path = get_env(shell->env, "HOME");
	else
		path = shell->cmd_table[1];
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		shell->exit_status = 1;
	}
	else
	{	
		getcwd(shell->cwd, sizeof(shell->cwd));
		set_env(&shell->env, "OLDPWD", old, 1);
		set_env(&shell->env, "PWD", shell->cwd, 1);
		shell->exit_status = 0;
	}
}
