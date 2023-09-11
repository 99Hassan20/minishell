/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:14:29 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/11 09:47:04 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_echo_option(char *option)
{
	int	i;

	if (option[0] != '-')
		return (0);
	i = 1;
	if (!option[i])
		return (0);
	while (option[i] && option[i] == 'n')
		i++;
	if (!option[i])
		return (1);
	return (0);
}

// void	ft_echo(t_shell *shell)
// {
// 	int		i;
// 	int		print_nl;

// 	i = 1;
// 	print_nl = 1;
// 	if (!shell->cmd_table[1])
// 	{
// 		printf("\n");
// 		return ;
// 	}
// 	while (shell->cmd_table[i] && is_valid_echo_option(shell->cmd_table[i]))
// 	{
// 		print_nl = 0;
// 		i++;
// 	}
// 	while (shell->cmd_table[i])
// 	{
// 		printf("%s", shell->cmd_table[i]);
// 		if (shell->cmd_table[i + 1])
// 			printf(" ");
// 		i++;
// 	}
// 	if (print_nl)
// 		printf("\n");
// 	shell->exit_status = 0;
// }

void	ft_echo(t_shell *shell, t_command command)
{
	int		i;
	int		print_nl;

	i = 1;
	print_nl = 1;
	if (!command.args[1])
	{
		printf("\n");
		return ;
	}
	while (command.args[i] && is_valid_echo_option(command.args[i]))
	{
		print_nl = 0;
		i++;
	}
	while (command.args[i])
	{
		printf("%s", command.args[i]);
		if (command.args[i + 1])
			printf(" ");
		i++;
	}
	if (print_nl)
		printf("\n");
	shell->exit_status = 0;
}
