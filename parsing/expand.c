/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:09:38 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/11 15:57:11 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	tmp = tokens;
	cmd_table = NULL;
	while (tmp)
	{
		str = ft_strdup("");
		if (tmp->type == PIPE || tmp->type == ARRED || tmp->type == SPACE
			|| tmp->type == LRED || tmp->type == RRED || tmp->type == ALRED)
		{
			if (tmp->type != SPACE)
				str = tmp->content;
			tmp = tmp->next;
		}
		else
		{
			while (tmp && (tmp->type == STR || (tmp->type == SPACE
						&& (tmp->state == INDQOUTES || tmp->state == INSQOUTES))
					|| tmp->type == VAR || tmp->type == DQUOTES
					|| tmp->type == SQUOTES))
			{
				if (!(tmp->type == DQUOTES || tmp->type == SQUOTES))
					str = ft_strjoin(str, tmp->content);
				tmp = tmp->next;
			}
		}
		if (str[0])
			cmd_table = append_to_array(cmd_table, str);
	}
	int i = 0;
	while (cmd_table[i])
	{
		printf("cmd_table[%d]: %s\n", i, cmd_table[i]);
		i++;
	}
	return (cmd_table);
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
			if (ft_strcmp(tmp->content, "$?") == 0)
				value = ft_itoa(shell->exit_status);
			else
				value = get_env(shell->env, tmp->content + 1);
			if (!value)
				value = "";
			tmp->content = value;
			tmp->length = ft_strlen(tmp->content);
			tmp->type = STR;
		}
		tmp = tmp->next;
	}
	// get_command_table(shell);
}
