/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:41:07 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/24 14:44:23 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGTERM)
	{
		printf("hello \n");
			// printf("\n");
			// rl_on_new_line();
			// rl_replace_line("", 0);
			// rl_redisplay();
			// g_exit_status = 1;
	}
	
	if (sig == SIGINT)
	{
		
		if (rl_catch_signals)
		{
			close(0);
			g_exit_status = 1;
		}
		else
		{	
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_exit_status = 1;
		}		
	}
}

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
	if (!herdocs)
		printf("No herdocs\n");
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
	printf("herdocs: \n");
	while (herdocs)
	{
		printf("file: %s | type: HERDOC\n", herdocs->file);
		herdocs = herdocs->next;
	}
	printf("args: ");
	print_cmd_table(command->args);
	printf("-------------------------------------------------------------\n");
}

int	parse_line(t_shell *shell, char *line)
{
	char	*trimmed;

	// g_exit_status = g_exit_status;
	trimmed = ft_strtrim(line, " \t\n\r");
	free(line);
	if (!*trimmed)
	{
		free(trimmed);
		return (0);
	}
	add_history(trimmed);
	lexer(shell, trimmed);
	if (has_error(shell))
	{
		free(trimmed);
		g_exit_status = 2;
		return (0);
	}
	expand(shell);
	// print_tokens(shell->tokens);
	split_cmds(shell);
	get_ready_commands(shell);
	// print_final_command(&shell->ready_commands[0]);
	
	// int i = 0; 
	// while (i < shell->cmd_count)
	// {
		// print_final_command(&shell->ready_commands[i]);
	// 	i++;
	// }
	// print_final_command(&shell->ready_commands[0]);
	free(trimmed);
	return (1);
}

void	shell_loop(t_shell *shell, char *prompt)
{
	char	*line;

	while (1)
	{
		getcwd(shell->cwd, sizeof(shell->cwd));
		set_env(&shell->env, "PWD", shell->cwd, 1);
		line = readline(prompt);
		if (!line)
		{
			free(line);
			exit(g_exit_status);
		}
		if (!parse_line(shell, line))
			continue ;
		execline(shell, env_to_array(shell->env));
		
	
	}
}

int	main(int __attribute__((unused))argc, char __attribute__((unused))**argv, char *env[])
{
	t_shell	shell;
	char	*prompt;

	prompt = "\033[38;5;206mminishell $>\033[0m ";
	// sigaction(SIGINT, &(struct sigaction){signal_handler}, NULL);
	signal(SIGINT, signal_handler);
	sigignore(SIGQUIT);
	// prompt = "minishell$> ";
	shell.env = NULL;
	rl_catch_signals = 0;
	env_to_list(&shell, env);
	shell_loop(&shell, prompt);
	return (shell.exit_status);
}
