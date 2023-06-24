/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:00:56 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/24 22:23:39 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *copy_token(t_token *token)
{
	t_token	*copy;

	copy = malloc(sizeof(t_token));
	if (!copy)
		return (NULL);
	copy->content = token->content;
	copy->length = token->length;
	copy->state = token->state;
	copy->type = token->type;
	copy->next = NULL;
	return (copy);
}

void	count_pipes(t_shell *shell)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->type == PIPE)
			count++;
		tmp = tmp->next;
	}
	shell->cmd_count = count + 1;
}

void	split_cmds(t_shell	*shell)
{	
	t_token	*tmp;
	int		i;

	count_pipes(shell);
	printf("commands: %d\n", shell->cmd_count);
	shell->commands = malloc(sizeof(t_token *) * shell->cmd_count);
	if (!shell->commands)
		return ;
	tmp = shell->tokens;
	i = 0;
	while (i < shell->cmd_count)
	{
		// cmd = NULL;
		shell->commands[i] = NULL;
		while (tmp && tmp->type != PIPE)
		{
			if (!(tmp->type == SPACE && tmp->state == DFAULT))
				append_token(&shell->commands[i], copy_token(tmp));
			tmp = tmp->next;
		}
		if (tmp && tmp->type == PIPE && tmp->next)
			tmp = tmp->next;
		i++;
	}
}

// t_cmds	*new_cmd(char *cmd, char **args, int argc)
// {
// 	t_cmds	*new;

// 	new = malloc(sizeof(t_cmds));
// 	if (!new)
// 		return (NULL);
// 	new->cmd = cmd;
// 	new->args = args;
// 	new->argc = argc;
// 	new->next = NULL;
// 	return (new);
// }

// void	append_cmd(t_cmds	**head, t_cmds *new)
// {
// 	t_cmds	*tmp;

// 	if (!*head)
// 		*head = new;
// 	else
// 	{
// 		tmp = *head;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = new;
// 	}
// }
