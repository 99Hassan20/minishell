/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:10:06 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/01 17:34:56 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_tokentype type, char *content, int length, t_state state)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	if (!new->content)
	{
		free(new);
		return (NULL);
	}
	new->length = length;
	new->state = state;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	append_token(t_token **tokens, t_token *new)
{
	t_token	*head;

	head = *tokens;
	if (*tokens)
	{
		while (head->next)
			head = head->next;
		head->next = new;
		return ;
	}
	*tokens = new;
}

t_token	*get_last_token(t_token *tokens)
{
	t_token	*last;

	last = tokens;
	while (last->next)
		last = last->next;
	return (last);
}

int	get_list_size(t_token *head)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	delete_token(t_token **head, char *content)
{
	t_token	*tmp;
	t_token	*to_delete;

	tmp = *head;
	if (tmp && ft_strcmp(tmp->content, content) == 0)
	{
		*head = NULL;
		return ;
	}
	while (tmp && tmp->next && ft_strcmp(tmp->next->content, content) != 0)
		tmp = tmp->next;
	if (tmp && tmp->next)
	{
		to_delete = tmp->next;
		tmp->next = to_delete->next;
		to_delete->next = NULL;
	}
}
