/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:34:56 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/01 08:31:28 by hoigag           ###   ########.fr       */
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

char *leak_free_join(char *s1, char *s2)
{
	char *tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (tmp);
}


char	**env_to_array(t_env *env)
{
	char	**env_array;
	int		i;
	t_env	*tmp;
	char	*tmp_str;
	char	*tmp_str2;

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
		tmp_str = leak_free_join(ft_strdup(env->key), ft_strdup("="));
		tmp_str2 = leak_free_join(ft_strdup(tmp_str), ft_strdup(env->value));
		free(tmp_str);
		env_array[i] = ft_strdup(tmp_str2);
		free(tmp_str2);
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
