/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:19:55 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/01 17:46:31 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_shell *shell)
{
	g_exit_status = 0;
	if (getcwd(shell->cwd, sizeof(shell->cwd)))
	{
		printf("%s\n", shell->cwd);
	}
	else
	{
		printf("pwd: error\n");
		g_exit_status = 1;
	}
}
