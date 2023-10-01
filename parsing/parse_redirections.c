/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:24:00 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/01 17:36:59 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_file_name(t_token **tokens)
{
	char	*file_name;
	char	*expand_herdoc;
	char	**args;

	args = init_data(&file_name, &expand_herdoc);
	if (!args)
		return (NULL);
	if ((*tokens)->type == _SPACE)
		free_single_token(tokens);
	while ((*tokens) && !is_redirection(*tokens))
	{
		if ((*tokens)->type == _SPACE && (*tokens)->state == DFAULT)
			break ;
		if ((*tokens)->type == DQUOTES || (*tokens)->type == SQUOTES)
		{
			free(expand_herdoc);
			expand_herdoc = NULL;
		}
		set_file_name(*tokens, &file_name);
		free_single_token(tokens);
	}
	args[0] = file_name;
	args[1] = expand_herdoc;
	args[2] = NULL;
	return (args);
}

void	go_to_next_redirection(t_token **tmp, char ***args)
{
	ft_free_2d(*args);
	*args = NULL;
	*tmp = (*tmp)->next;
}

void	set_redirections(t_token *tokens,
	t_redirec **redirs, t_redirec **herdocs, int expand_herdoc)
{
	char	*file_name;
	char	**args;
	t_token	*tmp;

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
		go_to_next_redirection(&tmp, &args);
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
	set_redirections(cmd, &command.redirections, &command.herdocs, 1);
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
