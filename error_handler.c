/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:24:28 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/08 13:11:18 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_error(t_shell *shell)
{
	int		error;
	t_token	*last;

	error = 0;
	last = get_last_token(shell->tokens);
	if (shell->tokens->content[0] == '|'
		|| shell->tokens->content[0] == '>'
		|| shell->tokens->content[0] == '<')
	{
		printf("minishell: syntax error near unexpected token\n");
		error = 1;
	}
	else if (last->content[0] == '|'
		|| last->content[0] == '>'
		|| last->content[0] == '<')
	{
		printf("minishell: syntax error near unexpected token\n");
		error = 1;
	}
	return (error);
}
