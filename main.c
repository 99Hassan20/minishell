/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:41:07 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/11 09:45:21 by hoigag           ###   ########.fr       */
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
		get_ready_commands(shell);
		execute_builtins2(shell, shell->ready_commands[0]);
		free(trimmed);
	}
}

int	main(int __attribute__((unused))argc, char __attribute__((unused))**argv, char __attribute__((unused))*env[])
{
	t_shell	shell;
	char	*prompt;

	prompt = "\033[38;5;206mminishell $>\033[0m ";
	shell.env = NULL;
	shell.exit_status = 0;
	env_to_list(&shell, env);
	shell_loop(&shell, prompt);
	return (shell.exit_status);
}
