/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:24:28 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/09 13:20:40 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redirection(t_token *token)
{
	if (token->type == RRED || token->type == LRED
		|| token->type == ARRED || token->type == ALRED)
		return (1);
	return (0);
}

int has_redirection_error(t_shell *shell)
{
	t_token *tmp;

	tmp = shell->tokens;
	while (tmp)
	{
		if (is_redirection(tmp))
		{
			if (!tmp->next || tmp->next->type != STR)
				return (1);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	has_error(t_shell *shell)
{
	int		error;
	t_token	*last;

	error = 0;
	last = get_last_token(shell->tokens);
	if (shell->tokens->content[0] == '|')
	{
		printf("minishell: syntax error near unexpected token\n");
		error = 1;
	}
	else if (shell->in_quotes)
	{
		printf("minishell: syntax error unclosed quote\n");
		error = 1;
	}
	else if (has_redirection_error(shell))
	{
		printf("minishell: syntax error near unexpected token\n");
		error = 1;
	}
	else if (last->content[0] == '|')
	{
		printf("minishell: syntax error near unexpected token\n");
		error = 1;
	}
	return (error);
}
