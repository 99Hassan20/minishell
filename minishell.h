/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:34:46 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/06 13:09:18 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define SPECIALS "|$ ><\"'"
# define DELIMITERS "| ><"

typedef	enum
{
	INDQOUTES,
	INSQOUTES,
	DFAULT,
} State;

typedef enum
{
	PIPE,
	SPACE,
	STR,
	VAR,
	RRED,
	LRED,
	ARRED,
	ALRED,
	DQUOTES,
	SQUOTES,
}	TokenType;

typedef struct s_token
{
	TokenType		type;
	char			*content;
	int				length;
	State			state;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	int		in_quotes;
	int		q_type;
	t_token	*tokens;
}	t_shell;

//token methods
t_token	*new_token(TokenType type, char *content, int length, State state);
// void	append_token_v2(t_token **tokens, TokenType type, char *content, int length, State state);
void	append_token(t_token **tokens, t_token *new);
void	print_tokens(t_token *tokens);
void	lexer(t_shell *shell, char *s);

#endif