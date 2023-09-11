/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:22:27 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/11 12:26:13 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_valid_variable(char *var)
{
	int	i;

	if (var[0] != '_' && !ft_isalpha(var[0]))
		return (0);
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(t_shell *shell, char **command)
{
	int		i;
	char	**pair;

	shell->exit_status = 0;
	i = 1;
	if (!command[1])
	{
		print_env(shell->env, 2);
		return ;
	}
	while (command[i])
	{
		if (check_valid_variable(command[i]))
		{
			pair = ft_split(command[i], '=');
			if (!pair[1] && ft_get_index_of(command[i], '=') != -1)
				pair[1] = ft_strdup("");
			if (ft_get_index_of(command[i], '=') != -1)
				set_env(&shell->env, pair[0], pair[1], 1);
			else
				set_env(&shell->env, pair[0], pair[1], 0);
		}
		else
		{
			shell->exit_status = 1;
			printf("minishell: export: `%s': not a valid identifier\n", shell->cmd_table[i]);
		}
		i++;
	}
}

// void	ft_export(t_shell *shell, t_command command)
// {
// 	int		i;
// 	char	**pair;

// 	shell->exit_status = 0;
// 	i = 1;
// 	if (!command.args[1])
// 	{
// 		print_env(shell->env, 2);
// 		return ;
// 	}
// 	while (command.args[i])
// 	{
// 		if (check_valid_variable(command.args[i]))
// 		{
// 			pair = ft_split(command.args[i], '=');
// 			if (!pair[1] && ft_get_index_of(command.args[i], '=') != -1)
// 				pair[1] = ft_strdup("");
// 			if (ft_get_index_of(command.args[i], '=') != -1)
// 				set_env(&shell->env, pair[0], pair[1], 1);
// 			else
// 				set_env(&shell->env, pair[0], pair[1], 0);
// 		}
// 		else
// 		{
// 			shell->exit_status = 1;
// 			printf("minishell: export: `%s': not a valid identifier\n", command.args[i]);
// 		}
// 		i++;
// 	}
// }


void	ft_unset(t_shell *shell, char **command)
{
	int	i;

	shell->exit_status = 0;
	if (!command[1])
		return ;
	i = 1;
	while (command[i])
	{
		if (check_valid_variable(command[i])
			&& ft_get_index_of(command[i], '=') == -1)
			unset_env(&shell->env, command[i]);
		else
		{
			printf("minishell: unset: \
`%s': not a valid identifier\n", command[i]);
			shell->exit_status = 1;
		}
		i++;
	}
}

// void	ft_unset(t_shell *shell, t_command command)
// {
// 	int	i;

// 	shell->exit_status = 0;
// 	if (!command.args[1])
// 		return ;
// 	i = 1;
// 	while (command.args[i])
// 	{
// 		if (check_valid_variable(command.args[i])
// 			&& ft_get_index_of(command.args[i], '=') == -1)
// 			unset_env(&shell->env, command.args[i]);
// 		else
// 		{
// 			printf("minishell: unset: \
// `%s': not a valid identifier\n", command.args[i]);
// 			shell->exit_status = 1;
// 		}
// 		i++;
// 	}
// }