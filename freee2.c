/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freee2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 08:52:52 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/01 23:29:09 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(t_token **commands, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		free_tokens(commands[i]);
		i++;
	}
	free(commands);
}

void	full_free(t_shell *shell)
{
	int	i;

	i = 0;
	free_tokens(shell->tokens);
	free_commands(shell->commands, shell->cmd_count);
	while (i < shell->cmd_count)
	{
		ft_free_2d(shell->ready_commands[i].args);
		free_redirections(&shell->ready_commands[i].redirections);
		free_redirections(&shell->ready_commands[i].herdocs);
		i++;
	}
	free(shell->ready_commands);
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->ready_commands = NULL;
}

void	free_single_token(t_token **tokens)
{
	t_token	*to_delete;

	to_delete = *tokens;
	(*tokens) = (*tokens)->next;
	free(to_delete->content);
	free(to_delete);
}

char	*leak_free_join(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (tmp);
}
