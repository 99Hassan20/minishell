/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:15:36 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/13 12:35:24 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

int	push_env(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = new_env(key, value);
	if (!new)
		return (-1);
	if (*env)
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*env = new;
	return (1);
}

void	env_to_list(t_shell *shell, char *env[])
{
	int		i;
	char	**pair;
	char	*ptr;

	i = 0;
	while (env[i])
	{
		if (ft_count(env[i], '=') == 1)
			pair = ft_split(env[i], '=');
		else
		{
			ptr = ft_strchr(env[i], '=');
			*ptr = 27;
			pair = ft_split(env[i], 27);
			*ptr = '=';
		}
		if (!pair)
			return ;
		if (!push_env(&shell->env, pair[0], pair[1]))
		{
			printf("could not add to env list\n");
			return ;
		}
		i++;
	}
}

void	print_env(t_env *head, int flag)
{
	while (head)
	{
		if (flag == 1)
		{
			if (head->value)
				printf("%s=%s\n", head->key, head->value);
		}
		else
		{
			if (head->value)
				printf("declare -x %s=\"%s\"\n", head->key, head->value);
			else
				printf("declare -x %s\n", head->key);
		}
		head = head->next;
	}
}

char	*get_env(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (key && ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
