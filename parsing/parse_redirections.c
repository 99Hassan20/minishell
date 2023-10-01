/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:24:00 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/01 15:39:33 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*copy_tokens(t_token *cmd)
{
	t_token	*tmp;
	t_token	*new;

	new = NULL;
	tmp = cmd;
	while (tmp)
	{
		append_token(&new,
			new_token(tmp->type, tmp->content, tmp->length, tmp->state));
		tmp = tmp->next;
	}
	return (new);
}

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

void	delete_single_token(t_token **tokens)
{
	t_token	*to_delete;

	to_delete = *tokens;
	(*tokens) = (*tokens)->next;
	free((to_delete)->content);
	free(to_delete);
}

char	**get_file_name(t_token **tokens)
{
	char	*file_name;
	char	*expand_herdoc;
	char	**args;
	char	*tmp_str;

	expand_herdoc = ft_strdup("expand");
	file_name = ft_strdup("");
	args = malloc(sizeof(char *) * 3);
	if (!args)
		return (NULL);
	if ((*tokens)->type == _SPACE)
		delete_single_token(&tokens);
	while ((*tokens) && !is_redirection(*tokens))
	{
		if ((*tokens)->type == _SPACE && (*tokens)->state == DFAULT)
			break ;
		if ((*tokens)->type == DQUOTES || (*tokens)->type == SQUOTES)
			expand_herdoc = NULL;
		if (((*tokens)->type != DQUOTES && (*tokens)->type != SQUOTES) || ((*tokens)->type == _SPACE && (*tokens)->state != DFAULT))
		{
			tmp_str = file_name;
			file_name = ft_strjoin(file_name, (*tokens)->content);
			free(tmp_str);
		}
		delete_single_token(&tokens);
	}
	args[0] = file_name;
	args[1] = expand_herdoc;
	args[2] = NULL;
	return (args);
}

void set_redirections(t_token *tokens, t_redirec **redirs, t_redirec **herdocs)
{
	char	*file_name;
	int		expand_herdoc;
	char	**args;
	t_token	*tmp;

	expand_herdoc = 1;
	args = NULL;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == ALRED && tmp->next)
		{
			args = get_file_name(&tmp->next);
			file_name = args[0];
			if (!args[1])
				expand_herdoc = 0;
			append_redirec(herdocs, file_name, tmp->type, expand_herdoc);
		}
		else if (is_redirection(tmp) && tmp->next)
		{
			args = get_file_name(&tmp->next);
			file_name = args[0];
			append_redirec(redirs, file_name, tmp->type, expand_herdoc);
		}
		ft_free_2d(args);
		args = NULL;
		tmp = tmp->next;
	}
}

t_command	get_final_command(t_token *cmd)
{
	t_command	command;
	t_token		*cpy;
	t_token		*noredir;

	cpy = copy_tokens(cmd);
	if (cmd && cmd->type == _SPACE)
		cmd = cmd->next;
	command.redirections = NULL;
	command.herdocs = NULL;
	set_redirections(cmd, &command.redirections, &command.herdocs);
	noredir = remove_redirections(cpy);
	free_tokens(cpy);
	command.args = get_command_table(noredir);
	free_tokens(noredir);
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
