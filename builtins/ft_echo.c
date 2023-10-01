/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:14:29 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/01 23:20:30 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_echo(t_shell __attribute__((unused))*shell, char **command)
{
	int		i;
	int		print_nl;

	i = 1;
	print_nl = 1;
	if (!command[1])
	{
		printf("\n");
		return ;
	}
	while (command[i] && is_valid_echo_option(command[i]))
	{
		print_nl = 0;
		i++;
	}
	while (command[i])
	{
		printf("%s", command[i]);
		if (command[i + 1])
			printf(" ");
		i++;
	}
	if (print_nl)
		printf("\n");
	g_exit_status = 0;
}
