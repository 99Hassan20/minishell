/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:41:07 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/10 17:16:08 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_final_command(t_command *command)
{
	printf("-------------------------------------------------------------\n");
	if (command->cmd)
		printf("cmd: %s\n", command->cmd);
	else
		printf("cmd: NULL\n");
	printf("redirections: ");
	t_redirec *tmp = command->redirections;
	if (!tmp)
		printf("No redirecitons\n");
	while (tmp)
	{
		if (tmp->type == RRED)
			printf("file: %s | type: RRED\n", tmp->file);
		else if (tmp->type == LRED)
			printf("file: %s | type: LRED\n", tmp->file);
		else if (tmp->type == ARRED)
			printf("file: %s | type: ARRED\n", tmp->file);
		else if (tmp->type == ALRED)
			printf("file: %s | type: ALRED\n", tmp->file);
		tmp = tmp->next;
	}
	printf("args: ");
	print_cmd_table(command->args);
	printf("-------------------------------------------------------------\n");
}


void remove_all_redir(t_token **token)
{
	t_token *tmp;
	t_token *red;
	t_token *file;

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
	t_redirec *tmp;
	t_redirec *new;

	
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
		return;
	}
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}



t_command get_final_command(t_token *cmd)
{
	t_command command;
	t_token *tmp;
	t_token *nospace;

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
			append_redirec(&command.redirections, tmp->next->content, tmp->type);
		tmp = tmp->next;
	}
	remove_all_redir(&cmd);
	command.args = get_command_table(cmd);
	return command;
}

void get_ready_commands(t_shell *shell)
{
	int i;

	shell->ready_commands = malloc(sizeof(t_command) * shell->cmd_count );
	if (!shell->ready_commands)
		return ;
	i = 0;
	while (i < shell->cmd_count)
	{
		shell->ready_commands[i] = get_final_command(shell->commands[i]);
		i++;
	}
}

void	shell_loop(t_shell *shell, char *prompt)
{
	char	*line;
	char	*trimmed;

	while (1)
	{
		getcwd(shell->cwd, sizeof(shell->cwd));
		set_env(&shell->env, "PWD", shell->cwd, 1);
		line = readline(prompt);
		if (!line)
		{
			free(line);
			exit(shell->exit_status);
		}
		trimmed = ft_strtrim(line, " \t\n\r");
		free(line);
		if (!*trimmed)
		{
			free(trimmed);
			continue ;
		}
		add_history(trimmed);
		lexer(shell, trimmed);
		if (has_error(shell))
		{
			free(trimmed);
			shell->exit_status = 2;
			continue ;
		}
		expand(shell);
		split_cmds(shell);
		int i = 0;
		get_ready_commands(shell);
		while (i < shell->cmd_count)
		{
			print_final_command(&shell->ready_commands[i]);
			i++;
		}
		free(trimmed);
	}
}

int	main(int __attribute__((unused))argc, char __attribute__((unused))**argv, char __attribute__((unused))*env[])
{
	t_shell	shell;
	char	*prompt;

	prompt = "\033[38;5;206mhoigag@minishell$\033[0m ";
	shell.env = NULL;
	env_to_list(&shell, env);
	shell_loop(&shell, prompt);
	return (shell.exit_status);
}
