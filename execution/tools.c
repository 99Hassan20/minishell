/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ou <abdel-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 11:38:25 by abdel-ou          #+#    #+#             */
/*   Updated: 2023/10/01 13:26:31 by abdel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***to3d_arr(t_shell *shell)
{
	char		***to_3d;
	int			i;

	i = 0; 
	to_3d = malloc(sizeof(char **) * (shell->cmd_count + 1));
	while (i < shell->cmd_count)
	{
		to_3d[i] = shell->ready_commands[i].args;
		i++;
	}
	to_3d[i] = NULL;
	return (to_3d);
}
