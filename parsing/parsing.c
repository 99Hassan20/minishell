/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:10:03 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/15 08:48:52 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_word(t_shell *shell, char *s, char **w, t_token **t)
{
	char	*word;
	t_token	*token;

	word = get_word(s, shell);
	if (shell->in_quotes)
		token = new_token(STR, word, ft_strlen(word), shell->q_type);
	else
		token = new_token(STR, word, ft_strlen(word), DFAULT);
	*w = word;
	*t = token;
}

void	parse_single_tokens(t_shell *shell, char *s, char **w, t_token **t)
{
	char	*word;
	t_token	*token;

	word = NULL;
	token = NULL;
	if (*s == ' ')
	{
		word = ft_strdup(" ");
		if (shell->in_quotes)
			token = new_token(_SPACE, word, 1, shell->q_type);
		else
			token = new_token(_SPACE, word, 1, DFAULT);
		*w = word;
		*t = token;
	}
	else if (*s == '|' && !shell->in_quotes)
		set_value(w, t, "|", PIPE);
	else if (*s == '>' && *(s + 1) == '>')
		set_value(w, t, ">>", ARRED);
	else if (*s == '<' && *(s + 1) == '<')
		set_value(w, t, "<<", ALRED);
	else if (*s == '>' && !shell->in_quotes)
		set_value(w, t, ">", RRED);
	else if (*s == '<' && !shell->in_quotes)
		set_value(w, t, "<", LRED);
}

void	parse_var(t_shell *shell, char *s, char **w, t_token **t)
{
	char	*word;
	t_token	*token;

	word = NULL;
	token = NULL;
	if (*s == '$' && (!*(s + 1) || is_delim(*(s + 1), shell)))
	{
		word = ft_strdup("$");
		if (shell->in_quotes)
			token = new_token(STR, word, ft_strlen(word), shell->q_type);
		else
			token = new_token(STR, word, ft_strlen(word), DFAULT);
	}
	else if (*s == '$')
	{
		word = get_var(s, shell);
		if (shell->in_quotes)
			token = new_token(VAR, word, ft_strlen(word), shell->q_type);
		else
			token = new_token(VAR, word, ft_strlen(word), DFAULT);
	}
	*w = word;
	*t = token;
}

void	parse_quotes(t_shell *shell, char c, char **w, t_token **t)
{
	if (c == '\"')
	{
		set_value(w, t, "\"", DQUOTES);
		shell->in_quotes = !shell->in_quotes;
		shell->q_type = INDQOUTES;
	}
	else if (c == '\'')
	{
		set_value(w, t, "\'", SQUOTES);
		shell->in_quotes = !shell->in_quotes;
		shell->q_type = INSQOUTES;
	}
}

void	lexer(t_shell *shell, char *s)
{
	char	*word;
	t_token	*token;

	shell->tokens = NULL;
	shell->in_quotes = 0;
	shell->q_type = -1;
	while (*s)
	{
		if (*s == ' ' && *(s + 1) == ' ' && !shell->in_quotes)
		{
			s++;
			continue ;
		}
		else if (is_char(*s, shell))
			parse_word(shell, s, &word, &token);
		else if (ft_strchr("><| ", *s))
			parse_single_tokens(shell, s, &word, &token);
		else if (*s == '$')
			parse_var(shell, s, &word, &token);
		else if (*s == '"' || *s == '\'')
			parse_quotes(shell, *s, &word, &token);
		append_token(&shell->tokens, token);
		s += ft_strlen(word);
	}
}
