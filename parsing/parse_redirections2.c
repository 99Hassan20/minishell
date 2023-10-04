/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 17:26:40 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/01 17:28:05 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redirection(t_token **new, t_token **tmp)
{
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	if ((*tmp)->type == _SPACE && (*tmp)->next)
	{
		append_token(new,
			new_token((*tmp)->type, (*tmp)->content,
				(*tmp)->length, (*tmp)->state));
		(*tmp) = (*tmp)->next;
	}
	while ((*tmp))
	{
		if (((*tmp)->type == _SPACE
				|| is_redirection((*tmp))
				|| (*tmp)->type == PIPE) && (*tmp)->state == DFAULT)
			break ;
		(*tmp) = (*tmp)->next;
	}
}

t_token	*remove_redirections(t_token *tokens)
{
	t_token	*tmp;
	t_token	*new;

	new = NULL;
	tmp = tokens;
	while (tmp)
	{
		if (is_redirection(tmp))
			add_redirection(&new, &tmp);
		else
		{
			append_token(&new,
				new_token(tmp->type, tmp->content, tmp->length, tmp->state));
			tmp = tmp->next;
		}
	}
	return (new);
}

void	append_redirec(t_redirec **head, char *file, int type, int exp)
{
	t_redirec	*tmp;
	t_redirec	*new;

	tmp = *head;
	new = malloc(sizeof(t_redirec));
	if (!new)
		return ;
	new->file = ft_strdup(file);
	new->type = type;
	new->expand_herdoc = exp;
	new->next = NULL;
	if (!tmp)
	{
		*head = new;
		return ;
	}
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

char	**init_data(char **file_name, char **expand_herdoc)
{
	char	**args;

	*file_name = ft_strdup("");
	*expand_herdoc = ft_strdup("expand");
	args = malloc(sizeof(char *) * 3);
	return (args);
}

void	set_file_name(t_token *tmp, char **file_name)
{
	char	*tmp_str;

	if ((tmp->type != DQUOTES && tmp->type != SQUOTES)
		|| (tmp->type == _SPACE && tmp->state != DFAULT))
	{
		tmp_str = *file_name;
		*file_name = ft_strjoin(*file_name, tmp->content);
		free(tmp_str);
	}
}
