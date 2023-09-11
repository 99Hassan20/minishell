/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:24:00 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/10 17:26:50 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_all_redir(t_token **token)
{
	t_token	*tmp;
	t_token	*red;
	t_token	*file;

	tmp = *token;
	if (is_redirection(tmp))
	{
		red = tmp;
		file = tmp->next;
		if (file && (file->type == STR || file->type == VAR))
			*token = file->next;
		else if (file && file->type == SPACE)
		{
			file = file->next;
			if (file && (file->type == STR || file->type == VAR))
				*token = file->next;
			else
				*token = tmp->next;
		}
		else
			*token = tmp->next;
	}
	while (tmp && tmp->next)
	{
		red = tmp->next;
		file = red->next;
		if (is_redirection(red) && file && (file->type == STR || file->type == VAR))
			tmp->next = file->next;
		else if (is_redirection(red) && file && file->type == SPACE)
		{
			file = file->next;
			if (file && (file->type == STR || file->type == VAR))
				tmp->next = file->next;
			else
				tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}

void	append_redirec(t_redirec **head, char *file, int type)
{
	t_redirec	*tmp;
	t_redirec	*new;

	
	tmp = *head;
	new = malloc(sizeof(t_redirec));
	if (!new)
		return ;
	new->file = file;
	new->type = type;
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

t_command	get_final_command(t_token *cmd)
{
	t_command	command;
	t_token		*tmp;
	t_token		*nospace;

	nospace = remove_space_from_tokens(cmd);
	tmp = nospace;
	if (cmd->type == SPACE)
		cmd = cmd->next;
	command.redirections = NULL;
	if (is_redirection(cmd))
		command.cmd = NULL;
	else
		command.cmd = ft_strdup(cmd->content);
	while (tmp)
	{
		if (is_redirection(tmp) && tmp->next)
			append_redirec(&command.redirections,
				tmp->next->content, tmp->type);
		tmp = tmp->next;
	}
	remove_all_redir(&cmd);
	command.args = get_command_table(cmd);
	return (command);
}

void	get_ready_commands(t_shell *shell)
{
	int	i;

	shell->ready_commands = malloc(sizeof(t_command) * shell->cmd_count);
	if (!shell->ready_commands)
		return ;
	i = 0;
	while (i < shell->cmd_count)
	{
		shell->ready_commands[i] = get_final_command(shell->commands[i]);
		i++;
	}
}
