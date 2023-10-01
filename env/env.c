/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:34:56 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/01 23:30:54 by hoigag           ###   ########.fr       */
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

int	env_size(t_env *env)
{
	int		i;
	t_env	*tmp;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**env_to_array(t_env *env)
{
	char	**env_array;
	int		i;
	char	*tmp_str;
	char	*tmp_str2;

	env_array = malloc(sizeof(char *) * (env_size(env) + 1));
	i = 0;
	while (env)
	{
		tmp_str = leak_free_join(ft_strdup(env->key), ft_strdup("="));
		tmp_str2 = leak_free_join(ft_strdup(tmp_str), ft_strdup(env->value));
		free(tmp_str);
		env_array[i] = ft_strdup(tmp_str2);
		free(tmp_str2);
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (free_env(env), env_array);
}
