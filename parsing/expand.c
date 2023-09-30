/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:09:38 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/30 14:11:45 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_quoted_string(t_token **head)
{
	char	*str;
	t_token	*tmp;

	str = "";
	tmp = *head;
	while (tmp)
	{
		if (tmp->type == DQUOTES || tmp->type == SQUOTES)
			break ;
		str = ft_strjoin(str, tmp->content);
		tmp = tmp->next;
	}
	if (tmp->type == DQUOTES || tmp->type == SQUOTES)
		*head = tmp->next;
	else
		*head = tmp;
	return (str);
}

char	**get_command_table(t_token *tokens)
{
	char	**cmd_table;
	t_token	*tmp;
	char	*str;
	int		is_space;
	char	*tmp_str;

	tmp = tokens;
	cmd_table = NULL;
	while (tmp)
	{
		is_space = 0;
		str = ft_strdup("");
		if (tmp->type == PIPE || tmp->type == ARRED || tmp->type == _SPACE
			|| tmp->type == LRED || tmp->type == RRED || tmp->type == ALRED)
		{
			if (tmp->type == _SPACE)
				is_space = 1;
			tmp = tmp->next;
		}
		else
		{
			while (tmp && (tmp->type == STR || (tmp->type == _SPACE
						&& (tmp->state == INDQOUTES || tmp->state == INSQOUTES))
					|| tmp->type == VAR || tmp->type == DQUOTES
					|| tmp->type == SQUOTES))
			{
				if (!(tmp->type == DQUOTES || tmp->type == SQUOTES))
				{
					tmp_str = str;
					str = ft_strjoin(str, tmp->content);
					free(tmp_str);
				}
				tmp = tmp->next;
			}
		}
		if (is_space == 0)
			cmd_table = append_to_array(cmd_table, str);
		free(str);
	}
	return (cmd_table);
}

void	expand(t_shell *shell)
{
	t_token	*tmp;
	char	*value;
	t_token	*new;
	char	**values;
	int		i;
	int		to_expand;
	char	*trimmed;

	to_expand = 1;
	tmp = shell->tokens;
	new = NULL;
	while (tmp)
	{
		if (tmp->type == ALRED)
			to_expand = 0;
		if (tmp->type == VAR
			&& (tmp->state == INDQOUTES || tmp->state == DFAULT) && to_expand)
		{
			if (ft_strcmp(tmp->content, "$?") == 0)
				value = ft_itoa(g_exit_status);
			else
				value = get_env(shell->env, tmp->content + 1);
			if (!value)
				value = "";
			if (tmp->state == INDQOUTES)
			{
				append_token(&new, new_token(STR, value,
					ft_strlen(value), tmp->state));
			}
			else
			{
				trimmed = ft_strtrim(value, " \t");
				values = ft_split(trimmed, ' ');
				free(trimmed);
				i = 0;
				while (values[i])
				{
					append_token(&new, new_token(STR, values[i],
							ft_strlen(values[i]), tmp->state));
					if (values[i + 1])
						append_token(&new, new_token(_SPACE, " ", 1, DFAULT));
					i++;	
				}
				ft_free_2d(values);
			}
		}
		else if (tmp->type == VAR && !to_expand)
		{
			append_token(&new, new_token(STR, tmp->content,
					ft_strlen(tmp->content), tmp->state));
			to_expand = 1;
		}
		else
		{
			append_token(&new, new_token(tmp->type, tmp->content,
					ft_strlen(tmp->content), tmp->state));
		}
		tmp = tmp->next;
	}
	free_tokens(shell->tokens);
	shell->tokens = new;
}
