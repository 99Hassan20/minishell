/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:34:46 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/07 20:22:08 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef enum e_state
{
	INDQOUTES,
	INSQOUTES,
	DFAULT,
}	t_state;

typedef enum e_toketype
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
}	t_tokentype;

typedef struct s_token
{
	t_tokentype		type;
	char			*content;
	int				length;
	t_state			state;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	int		in_quotes;
	int		q_type;
	t_token	*tokens;
}	t_shell;

//prsing utilities
int		is_char(int c, t_shell *shell);
int		is_delim(int c, t_shell *shell);
char	*get_word(char *s, t_shell *shell);
char	*get_var(char *s, t_shell *shell);
void	set_value(char **w, t_token **token, char *value, t_tokentype tt);
int		lexer(t_shell *shell, char *s);

//token methods
t_token	*new_token(t_tokentype type, char *content, int length, t_state state);
void	append_token(t_token **tokens, t_token *new);
void	print_tokens(t_token *tokens);

#endif