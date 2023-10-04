/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freee.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:02:34 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/01 13:04:30 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->content)
		free(token->content);
	free(token);
	token = NULL;
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free_token(tokens);
		tokens = tmp;
	}
}

void	free_env_node(t_env *env)
{
	if (!env)
		return ;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	if (env)
		free(env);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free_env_node(env);
		env = tmp;
	}
}

void	free_redirections(t_redirec **redirections)
{
	t_redirec	*tmp;
	t_redirec	*next;

	if (!redirections)
		return ;
	tmp = *redirections;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->file);
		free(tmp);
		tmp = next;
	}
	*redirections = NULL;
}
