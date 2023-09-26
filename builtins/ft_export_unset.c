/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:22:27 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/26 16:06:34 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_variable(char *var)
{
	int	i;

	if (!var || (var[0] != '_' && !ft_isalpha(var[0])))
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

char	*get_joinded_strings(char **strings)
{
	int		i;
	char	*joined;

	i = 0;
	joined = ft_strdup("");
	if (!strings || !strings[0])
		return (NULL);
	if (!strings[0][0])
		return (joined);
	while (strings[i])
	{
		if (strings[i + 1])
			strings[i] = ft_strjoin(strings[i], "=");
		joined = ft_strjoin(joined, strings[i]);
		i++;
	}
	return (joined);
}

void	ft_export(t_shell *shell, char **command)
{
	int		i;
	char	**pair;

	g_exit_status = 0;
	i = 1;
	while (command[i])
	{
		if (check_valid_variable(command[i]))
		{
			pair = ft_split(command[i], '=');
			if (!pair[1] && ft_get_index_of(command[i], '=') != -1)
				pair[1] = ft_strdup("");
			if (ft_get_index_of(command[i], '=') != -1)
				set_env(&shell->env, pair[0], get_joinded_strings(pair + 1), 1);
			else
				set_env(&shell->env, pair[0], get_joinded_strings(pair + 1), 0);
		}
		else
		{
			g_exit_status = 1;
			printf("minishell: export: `%s':\
 not a valid identifier\n", command[i]);
		}
		i++;
	}
}

void	ft_unset(t_shell *shell, char **command)
{
	int	i;

	g_exit_status = 0;
	if (!command[1])
		return ;
	i = 1;
	while (command[i])
	{
		if (check_valid_variable(command[i])
			&& ft_get_index_of(command[i], '=') == -1)
		{
			if (ft_strcmp(command[i], "_") != 0)
				unset_env(&shell->env, command[i]);
		}
		else
		{
			printf("minishell: unset: \
`%s': not a valid identifier\n", command[i]);
			g_exit_status = 1;
		}
		i++;
	}
}
