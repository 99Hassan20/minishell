/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:24:28 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/10 11:44:08 by hoigag           ###   ########.fr       */
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
	t_token *next;
	tmp = remove_space_from_tokens(shell->tokens);
	// print_tokens(tmp);
	while (tmp)
	{
		if (is_redirection(tmp))
		{
			next = tmp->next;
			if (!next || (next->type != STR && next->type != VAR && next->type != DQUOTES && next->type != SQUOTES))
				return (1);
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
