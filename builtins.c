/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:09:59 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/11 12:16:05 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_env(t_shell *shell)
{
	int	i;

	i = 1;
	while (shell->cmd_table[i])
	{
		if (ft_strcmp(shell->cmd_table[i], "env") != 0)
		{
			printf("env: %s: No such file or directory\n", shell->cmd_table[i]);
			return ;
		}
		i++;
	}
	print_env(shell->env);
}

int	is_valid_echo_option(char *option)
{
	int	i;

	if (option[0] != '-')
		return (0);
	i = 1;
	while (option[i] && option[i] == 'n')
		i++;
	if (!option[i])
		return (1);
	return (0);
}

static void	ft_echo(t_shell *shell)
{
	int		i;
	int		print_nl;

	i = 1;
	print_nl = 1;
	print_cmd_table(shell);
	if (!shell->cmd_table[1])
	{
		printf("\n");
		return ;
	}
	while (shell->cmd_table[i] && is_valid_echo_option(shell->cmd_table[i]))
	{
		print_nl = 0;
		i++;
	}
	while (shell->cmd_table[i])
	{
		printf("%s", shell->cmd_table[i]);
		if (shell->cmd_table[i + 1])
			printf(" ");
		i++;
	}
	if (print_nl)
		printf("\n");
}

void	execute_builtins(t_shell *shell)
{
	if (ft_strcmp(shell->cmd_table[0], "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(shell->cmd_table[0], "echo") == 0)
		ft_echo(shell);
}
