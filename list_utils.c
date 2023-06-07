/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:10:06 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/07 20:19:52 by hoigag           ###   ########.fr       */
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
// void	append_token_v2(t_token **tokens, TokenType type, char *content, int length, State state)
// {
// 	t_token *head;
// 	t_token *new = new_token(type, content, length, state);
// 	head = *tokens;
// 	if (*tokens)
// 	{
// 		while (head->next)
// 			head = head->next;
// 		head->next = new;
// 		return;
// 	}
// 	*tokens = new;
// }

void	print_tokens(t_token *tokens)
{
	char *state[] = {"INDQOUTES", "INSQOUTES", "DFAULT"};
	char *type[] = {"PIPE", "SPACE", "STR", "VAR", "RRED", "LRED", "ARRED", "ALRED", "DQUOTES", "SQUOTES"};

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
// int main()
// {
//     t_token *head = NULL;
//     t_token *T = new_token(STR, "echo", 4, DFAULT);
//     t_token *T2 = new_token(STR, "hello", 5, DFAULT);
//     t_token *T3 = new_token(STR, "world", 5, DFAULT);
//     append_token(&head, T);
//     append_token(&head, T2);
//     append_token(&head, T3);
//     print_tokens(head);
//     return 0;
// }
