/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:19:55 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/11 09:47:59 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_pwd(t_shell *shell)
// {
// 	if (getcwd(shell->cwd, sizeof(shell->cwd)))
// 		printf("%s\n", shell->cwd);
// 	else
// 		printf("pwd: error\n");
// }

void	ft_pwd(t_shell *shell)
{
	if (getcwd(shell->cwd, sizeof(shell->cwd)))
		printf("%s\n", shell->cwd);
	else
		printf("pwd: error\n");
}
