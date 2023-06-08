/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:41:07 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/08 11:43:12 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(t_shell *shell, char *prompt)
{
	char	*line;
	char	*trimmed;

	while (1)
	{
		line = readline(prompt);
		if (!line)
		{
			printf("%sexit\n", prompt);
			free(line);
			exit(0);
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
		if (!has_error(shell))
			print_tokens(shell->tokens);
		free(trimmed);
	}
}

int	main(void)
{
	t_shell	shell;
	char	*prompt;

	prompt = "\033[38;5;206mhoigag@minishell$\033[0m ";
	shell_loop(&shell, prompt);
	return (0);
}
