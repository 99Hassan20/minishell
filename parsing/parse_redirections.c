/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:24:00 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/23 11:38:28 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		else if (file && file->type == _SPACE)
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
		if (is_redirection(red) && file
			&& (file->type == STR || file->type == VAR))
			tmp->next = file->next;
		else if (is_redirection(red) && file && file->type == _SPACE)
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

void	append_redirec(t_redirec **head, char *file, int type, int expand_herdoc)
{
	t_redirec	*tmp;
	t_redirec	*new;

	tmp = *head;
	new = malloc(sizeof(t_redirec));
	if (!new)
		return ;
	new->file = file;
	new->type = type;
	new->expand_herdoc = expand_herdoc;
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

char	**get_file_name(t_token **tokens)
{
	char   *file_name;
	char 	*expand_herdoc;
	char  	**args;

	expand_herdoc = "expand";
	file_name = "";
	args = malloc(sizeof(char *) * 2);
	if (!args)
		return (NULL);
	if ((*tokens)->type == _SPACE)
		(*tokens) = (*tokens)->next;
	while ((*tokens) && (*tokens)->type != _SPACE)
	{
		if ((*tokens)->type == DQUOTES || (*tokens)->type == SQUOTES)
			expand_herdoc = NULL;
		if ((*tokens)->type != DQUOTES && (*tokens)->type != SQUOTES)
			file_name = ft_strjoin(file_name, (*tokens)->content);
		*tokens = (*tokens)->next;
	}
	args[0] = file_name;
	args[1] = expand_herdoc;
	return (args);
}

void set_redirections(t_token *tokens, t_redirec **redirs, t_redirec **herdocs)
{
	char *file_name;
	int	expand_herdoc;
	char **args;

	expand_herdoc = 1;
	while (tokens)
	{
		if (tokens->type == ALRED && tokens->next)
		{
			args = get_file_name(&tokens->next);
			file_name = args[0];
			if (!args[1])
				expand_herdoc = 0;
			append_redirec(herdocs, file_name, tokens->type, expand_herdoc);
		}
		else if (is_redirection(tokens) && tokens->next)
		{
			args = get_file_name(&tokens->next);
			file_name = args[0];
			append_redirec(redirs, file_name, tokens->type, expand_herdoc);		
		}
		tokens = tokens->next;
	}
}


t_command	get_final_command(t_token *cmd)
{
	t_command	command;
	// t_token		*tmp;
	// t_token		*nospace;

	// nospace = remove_space_from_tokens(cmd);
	// tmp = nospace;
	if (cmd && cmd->type == _SPACE)
		cmd = cmd->next;
	command.redirections = NULL;
	command.herdocs = NULL;
	set_redirections(cmd, &command.redirections, &command.herdocs);
	remove_all_redir(&cmd);
	command.args = get_command_table(cmd);
	if (command.args && command.args[0])
		command.cmd = command.args[0];
	else
		command.cmd = NULL;
	return (command);
} 

void	get_ready_commands(t_shell *shell)
{
	int	i;

	if (shell->cmd_count == 0)
		return ;
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
