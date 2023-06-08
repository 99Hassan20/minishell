/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:09:38 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/08 19:06:45 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(t_shell *shell)
{
	t_token	*tmp;
	char	*value;

	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->type == VAR && (tmp->state == INDQOUTES || tmp->state == DFAULT))
		{
			value = get_env(shell->env, tmp->content + 1);
			if (!value)
				value = "";
			tmp->content = value;
		}
		tmp = tmp->next;
	}
}
