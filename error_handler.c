/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:24:28 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/25 17:12:02 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == RRED || token->type == LRED
		|| token->type == ARRED || token->type == ALRED)
		return (1);
	return (0);
}

int	has_redirection_error(t_shell *shell)
{
	t_token	*tmp;
	t_token	*next;

	tmp = remove_space_from_tokens(shell->tokens);
	while (tmp)
	{
		if (is_redirection(tmp))
		{
			next = tmp->next;
			if (!next || (next->type != STR && next->type != VAR
					&& next->type != DQUOTES && next->type != SQUOTES))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	has_pipe_error(t_shell *shell)
{
	t_token	*tmp;
	t_token	*next;

	tmp = remove_space_from_tokens(shell->tokens);
	while (tmp && tmp->next)
	{
		next = tmp->next;
		if (tmp->type == PIPE && next->type != STR
			&& next->type != VAR && next->type != DQUOTES
			&& next->type != SQUOTES && next->type != RRED && !is_redirection(next))
			return (1);
		tmp = tmp->next;
	}
	if (tmp && tmp->type == PIPE)
		return (1);
	return (0);
}

int	has_error(t_shell *shell)
{
	if (shell->tokens->type == PIPE)
	{
		printf("minishell: syntax error near unexpected token\n");
		return (1);
	}
	else if (shell->in_quotes)
	{
		printf("minishell: unexpected EOF while looking for matching\n");
		return (1);
	}
	else if (has_redirection_error(shell))
	{
		printf("minishell: syntax error near unexpected token\n");
		return (1);
	}
	else if (has_pipe_error(shell))
	{
		printf("minishell: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}
