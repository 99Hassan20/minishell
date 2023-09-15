/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:10:06 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/15 08:48:52 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_tokentype type, char *content, int length, t_state state)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = content;
	new->length = length;
	new->state = state;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	append_token(t_token **tokens, t_token *new)
{
	t_token	*head;

	head = *tokens;
	if (*tokens)
	{
		while (head->next)
			head = head->next;
		head->next = new;
		return ;
	}
	*tokens = new;
}

t_token	*get_last_token(t_token *tokens)
{
	t_token	*last;

	last = tokens;
	while (last->next)
		last = last->next;
	return (last);
}

int	get_list_size(t_token *head)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	delete_token(t_token **head, char *content)
{
	t_token	*tmp;
	t_token	*to_delete;

	tmp = *head;
	if (tmp && ft_strcmp(tmp->content, content) == 0)
	{
		*head = NULL;
		return ;
	}
	while (tmp && tmp->next && ft_strcmp(tmp->next->content, content) != 0)
		tmp = tmp->next;
	if (tmp && tmp->next)
	{
		to_delete = tmp->next;
		tmp->next = to_delete->next;
		to_delete->next = NULL;
	}
}

void	print_echo(t_token *tmp)
{
	while (tmp)
	{
		printf("%s", tmp->content);
		if (tmp->next)
			printf(" ");
		tmp = tmp->next;
	}
}

void	print_tokens(t_token *tokens)
{
	char *state[] = {"INDQOUTES", "INSQOUTES", "DFAULT"};
	char *type[] = {"PIPE", "_SPACE", "STR", "VAR", "RRED", "LRED", "ARRED", "ALRED", "DQUOTES", "SQUOTES"};

	printf("\033[1;33m"); // Set the color to yellow (for table headers)
	printf("\033[1;35m"); // Set the color to magenta (for table border)
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("| \033[1;33m%-10s\033[1;35m | \033[1;33m%-10s\033[1;35m | \033[1;33m%-10s\033[1;35m | \033[1;33m%-10s\033[1;35m |\n", "Token", "Type", "Length", "State");
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

	while (tokens)
	{
		printf("\033[1;37m"); // Set the color to white (for table content)
		printf("\033[1;35m|\033[0m %-10s \033[1;35m|\033[0m %-10s |\033[0m %-10d \033[1;35m|\033[0m %-10s \033[1;35m|\033[0m\n",
			   tokens->content, type[tokens->type], tokens->length, state[tokens->state]);
		printf("\033[1;35m"); // Set the color to magenta (for table border)
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		tokens = tokens->next;
	}

	printf("\033[0m"); // Reset the color to default
}