/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:22:27 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/17 13:47:24 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_valid_variable(char *var)
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

void	ft_export(t_shell *shell)
{
	int		i;
	char	**pair;

	shell->exit_status = 0;
	i = 1;
	if (!shell->cmd_table[1])
	{
		print_env(shell->env, 2);
		return ;
	}
	while (shell->cmd_table[i])
	{
		if (check_valid_variable(shell->cmd_table[i]))
		{
			pair = ft_split(shell->cmd_table[i], '=');
			if (!pair[1] && ft_get_index_of(shell->cmd_table[i], '=') != -1)
				pair[1] = ft_strdup("");
			set_env(&shell->env, pair[0], pair[1], 1);
		}
		else
		{
			shell->exit_status = 1;
			printf("minishell: export: `%s': not a valid identifier\n", shell->cmd_table[i]);
		}
		i++;
	}
}

void	ft_unset(t_shell *shell)
{
	int	i;

	shell->exit_status = 0;
	if (!shell->cmd_table[1])
		return ;
	i = 1;
	while (shell->cmd_table[i])
	{
		if (check_valid_variable(shell->cmd_table[i])
			&& ft_get_index_of(shell->cmd_table[i], '=') == -1)
			unset_env(&shell->env, shell->cmd_table[i]);
		else
		{
			printf("minishell: unset: \
`%s': not a valid identifier\n", shell->cmd_table[i]);
			shell->exit_status = 1;
		}
		i++;
	}
}
