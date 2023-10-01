/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 17:32:22 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/01 17:55:51 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_final_command(t_command *command)
{
	printf("-------------------------------------------------------------\n");
	if (command->cmd)
		printf("cmd: %s\n", command->cmd);
	else
		printf("cmd: NULL\n");
	printf("redirections: ");
	t_redirec *tmp = command->redirections;
	t_redirec *herdocs = command->herdocs;
	if (!tmp)
		printf("No redirecitons\n");
	else
		printf("\n|%10s	|%10s	|\n", "file", "type");
	while (tmp)
	{
		if (tmp->type == RRED)
			printf("|%10s|%10s	|\n", tmp->file, "RRED");
		else if (tmp->type == LRED)
			printf("|%10s|%10s	|\n", tmp->file, "LRED");
		else if (tmp->type == ARRED)
			printf("|%10s|%10s	|\n", tmp->file, "ARRED");
		else if (tmp->type == ALRED)
			printf("|%10s|%10s	|\n", tmp->file, "ALRED");
		tmp = tmp->next;
	}
	printf("herdocs: ");
	if (!herdocs)
		printf("No herdocs\n");
	else
		printf("\n|%10s|%10s	|\n", "file", "type");
	while (herdocs)
	{
		printf("|%10s|%10s	|\n", herdocs->file, "HEREDOC");
		herdocs = herdocs->next;
	}
	printf("args: ");
	print_cmd_table(command->args);
	printf("-------------------------------------------------------------\n");
}

void	print_echo(t_token *tmp)
{
	while (tmp)
	{
		printf("%s", tmp->content);
		if (tmp->next)
			printf(" ");
		tmp = tmp->next;
	}
}

void	print_tokens(t_token *tokens)
{
	char *state[] = {"INDQOUTES", "INSQOUTES", "DFAULT"};
	char *type[] = {"PIPE", "_SPACE", "STR", "VAR", "RRED", "LRED", "ARRED", "ALRED", "DQUOTES", "SQUOTES"};

	printf("\033[1;33m"); // Set the color to yellow (for table headers)
	printf("\033[1;35m"); // Set the color to magenta (for table border)
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("| \033[1;33m%-10s\033[1;35m | \033[1;33m%-10s\033[1;35m | \033[1;33m%-10s\033[1;35m | \033[1;33m%-10s\033[1;35m |\n", "Token", "Type", "Length", "State");
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	while (tokens)
	{
		printf("\033[1;37m"); // Set the color to white (for table content)
		printf("\033[1;35m|\033[0m %-10s \033[1;35m|\033[0m %-10s |\033[0m %-10d \033[1;35m|\033[0m %-10s \033[1;35m|\033[0m\n",
			   tokens->content, type[tokens->type], tokens->length, state[tokens->state]);
		printf("\033[1;35m"); // Set the color to magenta (for table border)
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		tokens = tokens->next;
	}

	printf("\033[0m"); // Reset the color to default
}

void print_all_ready_commands(t_shell *shell)
{
	int i = 0;

	while (i < shell->cmd_count)
	{
		print_final_command(&shell->ready_commands[i]);
		i++;
	}
}