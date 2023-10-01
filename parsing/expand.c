/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:09:38 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/01 15:13:34 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(t_shell *shell, int to_expand)
{
	t_token	*tmp;
	t_token	*new;

	tmp = shell->tokens;
	new = NULL;
	while (tmp)
	{
		if (tmp->type == ALRED)
			to_expand = 0;
		if (is_expandable(tmp, to_expand))
			expand_var(shell, tmp, &new);
		else if (tmp->type == VAR && !to_expand)
		{
			append_token(&new, new_token(STR, tmp->content,
					ft_strlen(tmp->content), tmp->state));
			to_expand = 1;
		}
		else
			append_token(&new, new_token(tmp->type, tmp->content,
					ft_strlen(tmp->content), tmp->state));
		tmp = tmp->next;
	}
	free_tokens(shell->tokens);
	shell->tokens = new;
}
