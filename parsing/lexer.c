/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:10:03 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/30 15:29:46 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	parse_word(t_shell *shell, char *s)
{
	t_token *token;
	char *word;
	int len;
	word = get_word(s, shell);
	len = ft_strlen(word);
	if (shell->in_quotes)
		token = new_token(STR, word, ft_strlen(word), shell->q_type);
	else
		token = new_token(STR, word, ft_strlen(word), DFAULT);
	free(word);
	append_token(&shell->tokens, token);

	return (len);
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
	char	*tmp = s;
	char	*word;
	t_token	*token;

	shell->tokens = NULL;
	shell->in_quotes = 0;
	shell->q_type = -1;
	while (*tmp)
	{
		if (*tmp == ' ' && *(tmp + 1) == ' ' && !shell->in_quotes)
		{
			tmp++;
			continue ;
		}
		else if (is_char(*tmp, shell))
		{
			tmp += parse_word(shell, tmp);
			continue;
		}
		else if (ft_strchr("><| ", *tmp))
			parse_single_tokens(shell, tmp, &word, &token);
		else if (*tmp == '$')
			parse_var(shell, s, &word, &token);
		else if (*tmp == '"' || *tmp == '\'')
			parse_quotes(shell, *tmp, &word, &token);
		append_token(&shell->tokens, token);
	
		tmp += ft_strlen(word);
		free(word);
	}
}
