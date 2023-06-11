/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:09:38 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/11 15:18:00 by hoigag           ###   ########.fr       */
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

void	get_command_table(t_shell *shell)
{
	char	**cmd_table;
	t_token	*tmp;

	tmp = shell->tokens;
	cmd_table = NULL;
	while (tmp)
	{
		if (tmp->type == DQUOTES || tmp->type == SQUOTES)
			cmd_table = append_to_array(cmd_table, get_quoted_string(&tmp->next));
		else if (tmp->type == STR || tmp->type == PIPE || tmp->type == ARRED
			|| tmp->type == LRED || tmp->type == RRED || tmp->type == ALRED)
			cmd_table = append_to_array(cmd_table, tmp->content);
		tmp = tmp->next;
	}
	shell->cmd_table = cmd_table;
}

void	expand(t_shell *shell)
{
	t_token	*tmp;
	char	*value;

	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->type == VAR && (tmp->state == INDQOUTES || tmp->state == DFAULT))
		{
			value = get_env(shell->env, tmp->content + 1);
			if (!value)
				value = "";
			tmp->content = value;
			tmp->length = ft_strlen(tmp->content);
			tmp->type = STR;
		}
		tmp = tmp->next;
	}
	get_command_table(shell);
}


