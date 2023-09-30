/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:00:56 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/30 17:47:27 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*copy_token(t_token *token)
{
	t_token	*copy;

	copy = ft_malloc(sizeof(t_token));
	if (!copy)
		return (NULL);
	copy->content = ft_strdup(token->content);
	if (!copy->content)
	{
		free(copy);
		return (NULL);
	}
	copy->length = token->length;
	copy->state = token->state;
	copy->type = token->type;
	copy->next = NULL;
	return (copy);
}

void	count_pipes(t_shell *shell)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->type == PIPE)
			count++;
		tmp = tmp->next;
	}
	shell->cmd_count = count + 1;
}

t_token	*remove_space_from_tokens(t_token *tokens)
{
	t_token	*new;
	t_token	*tmp;

	new = NULL;
	tmp = tokens;
	while (tmp)
	{
		if (!(tmp->type == _SPACE && tmp->state == DFAULT))
			append_token(&new, copy_token(tmp));
		tmp = tmp->next;
	}
	return (new);
}

void	split_cmds(t_shell	*shell)
{
	t_token	*tmp;
	int		i;
	t_token *cpy;

	count_pipes(shell);
	shell->commands = ft_malloc(sizeof(t_token *) * shell->cmd_count);
	if (!shell->commands)
		return ;
	tmp = shell->tokens;
	i = 0;
	while (i < shell->cmd_count)
	{
		shell->commands[i] = NULL;
		while (tmp && tmp->type != PIPE)
		{
			cpy = copy_token(tmp);
			printf(">>>>>> <%p>    <%p> <<<<<<<\n", tmp, cpy);
			append_token(&shell->commands[i], cpy);
			tmp = tmp->next;
		}
		if (tmp && tmp->type == PIPE && tmp->next)
			tmp = tmp->next;
		i++;
	}
		t_token *tmp2 = shell->commands[0];
		while (tmp2)
		{
			printf("%p ", tmp2);
			tmp2 = tmp2->next;
		}
		printf("\n");
}
