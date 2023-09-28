/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:41:07 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/25 18:31:47 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
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
			// rl_replace_line("", 0);
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
	else
		printf("\n|%10s|%10s	|\n", "file", "type");
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

int	parse_line(t_shell *shell, char *line)
{
	char	*trimmed;

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
	int i = 0;
	while (i < shell->cmd_count)
	{
		print_final_command(&shell->ready_commands[i]);
		i++;
	}
	int j = 0;
	while (j < shell->cmd_count)
	{
		free_tokens(shell->commands[j]);
		j++;
	}
	free(trimmed);
	return (1);
}

void	shell_loop(t_shell *shell, char *prompt)
{
	char	*line;
	int std_in;

	std_in = dup(0);
	// int		fd = 0;
	while (1)
	{
		getcwd(shell->cwd, sizeof(shell->cwd));
		// set_env(&shell->env, "PWD", shell->cwd, 1);
		line = readline(prompt);
		if (!line)
		{
			free(line);
			free_tokens(shell->tokens);
			exit(g_exit_status);
		}
		if (!parse_line(shell, line))
		{
			free_tokens(shell->tokens);
			shell->tokens = NULL;
			continue ;
		}
		// execline(shell, env_to_array(shell->env));
		dup2(std_in, 0);
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
}

int	main(int __attribute__((unused))argc, char __attribute__((unused))**argv, char *env[])
{
	t_shell	shell;
	char	*prompt;

	// prompt = "\033[38;5;206mminishell $>\033[0m ";
	// sigaction(SIGINT, &(struct sigaction){signal_handler}, NULL);
	signal(SIGINT, signal_handler);
	// sigignore(SIGQUIT);
	prompt = "minishell $> ";
	shell.env = NULL;
	shell.tokens = NULL;
	rl_catch_signals = 0;
	env_to_list(&shell, env);
	shell_loop(&shell, prompt);
	return (shell.exit_status);
}
