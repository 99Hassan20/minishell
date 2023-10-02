/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ou <abdel-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 15:13:36 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/02 13:39:58 by abdel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_quoted_string(t_token **tmp, char **str)
{
	char	*tmp_str;

	while ((*tmp) && ((*tmp)->type == STR || ((*tmp)->type == _SPACE
				&& ((*tmp)->state == INDQOUTES || (*tmp)->state == INSQOUTES))
			|| (*tmp)->type == VAR || (*tmp)->type == DQUOTES
			|| (*tmp)->type == SQUOTES))
	{
		if (!((*tmp)->type == DQUOTES || (*tmp)->type == SQUOTES))
		{
			tmp_str = *str;
			*str = ft_strjoin(*str, (*tmp)->content);
			free(tmp_str);
		}
		(*tmp) = (*tmp)->next;
	}
}

char	**get_command_table(t_token *tokens)
{
	char	**cmd_table;
	t_token	*tmp;
	char	*str;
	int		is_space;

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
			get_quoted_string(&tmp, &str);
		if (is_space == 0)
			cmd_table = append_to_array(cmd_table, str);
		free(str);
	}
	return (cmd_table);
}

void	handle_quoted_var(t_token **new, char *value, t_token *tmp)
{
	char	*trimmed;
	char	**values;
	int		i;

	trimmed = ft_strtrim(value, " \t");
	values = ft_split(trimmed, ' ');
	free(trimmed);
	i = 0;
	while (values[i])
	{
		append_token(new, new_token(STR, values[i],
				ft_strlen(values[i]), tmp->state));
		if (values[i + 1])
			append_token(new, new_token(_SPACE, " ", 1, DFAULT));
		i++;
	}
	ft_free_2d(values);
}

void	expand_var(t_shell *shell, t_token *tmp, t_token **new)
{
	char	*value;

	if (ft_strcmp(tmp->content, "$?") == 0)
		value = ft_itoa(g_exit_status);
	else
		value = get_env(shell->env, tmp->content + 1);
	if (!value)
		value = ft_strdup("");
	if (tmp->state == INDQOUTES)
		append_token(new, new_token(STR, value,
				ft_strlen(value), tmp->state));
	else
		handle_quoted_var(new, value, tmp);
	if (value)
		free(value);
}

int	is_expandable(t_token *tmp, int to_expand)
{
	if (tmp->type == VAR
		&& (tmp->state == INDQOUTES || tmp->state == DFAULT) && to_expand)
		return (1);
	return (0);
}
