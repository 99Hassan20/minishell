/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:41:07 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/01 23:39:59 by hoigag           ###   ########.fr       */
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
			rl_replace_line("", 0);
			rl_redisplay();
			g_exit_status = 1;
		}
	}
	else if (sig == SIGQUIT)
		return ;
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
	expand(shell, 1);
	split_cmds(shell);
	get_ready_commands(shell);
	free(trimmed);
	return (1);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	shell_loop(t_shell *shell, char *prompt)
{
	char	*line;
	int		std_in;

	std_in = dup(0);
	while (1)
	{
		getcwd(shell->cwd, sizeof(shell->cwd));
		line = readline(prompt);
		if (!line)
		{
			free(line);
			exit(g_exit_status);
		}
		if (!parse_line(shell, line))
		{
			free_tokens(shell->tokens);
			continue ;
		}
		execline(shell, env_to_array(shell->env));
		dup2(std_in, 0);
		full_free(shell);
		// system("leaks minishell -q");
	}
}

int	main(int argc, char **argv, char *env[])
{
	t_shell	shell;
	char	*prompt;

	(void)argc;
	(void)argv;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	prompt = "minishell $> ";
	shell.env = NULL;
	shell.tokens = NULL;
	shell.commands = NULL;
	shell.ready_commands = NULL;
	shell.cmd_table = NULL;
	rl_catch_signals = 0;
	env_to_list(&shell, env);
	shell_loop(&shell, prompt);
	return (shell.exit_status);
}
