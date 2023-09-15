/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:34:56 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/15 08:48:52 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_env(t_env **env, char *key, char *value, int overrite)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp && ft_strcmp(tmp->key, key) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (push_env(env, key, value));
	if (tmp && overrite)
		tmp->value = value;
	return (1);
}

int	unset_env(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*to_delete;

	tmp = *env;
	while (tmp->next && ft_strcmp(tmp->next->key, key) != 0)
		tmp = tmp->next;
	if (tmp->next)
	{
		to_delete = tmp->next;
		tmp->next = to_delete->next;
		to_delete->next = NULL;
		free(to_delete);
		return (1);
	}
	return (-1);
}

char	**env_to_array(t_env *env)
{
	char	**env_array;
	int		i;
	t_env	*tmp;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env_array = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		env_array[i] = ft_strjoin(ft_strjoin(env->key, "="), env->value);
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
