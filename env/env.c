/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:34:56 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/17 15:06:39 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
