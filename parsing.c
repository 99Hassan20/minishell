/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:10:03 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/06 20:17:56 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_char(int c, t_shell *shell)
{
	char	*specials;

	if (shell->in_quotes && shell->q_type == INDQOUTES)
		specials = "\" $";
	else if (shell->in_quotes && shell->q_type == INSQOUTES)
		specials = "\' $";
	else
		specials = "|$ ><\"'";
	return (!ft_strchr(specials, c));
}

static int	is_delim(int c, t_shell *shell)
{
	return (!is_char(c, shell));
}

static char	*parse_string(char *s, t_shell *shell)
{
	int		i;

	i = 0;
	while (s[i] && is_char(s[i], shell))
	{
		if (s[i] == '$' && (is_char(s[i + 1], shell) || s[i + 1] == '$'))
			break ;
		i++;
	}
	return (ft_substr(s, 0, i));
}

static char	*parse_var(char *s, t_shell *shell)
{
	int		i;
	char	*delim;

	i = 1;
	if (shell->in_quotes)
		delim = " \"'";
	else
		delim = "| ><\"'";
	if (s[i] == '$')
		return (ft_substr(s, 0, i + 1));
	while (s[i])
	{
		if (ft_strchr(delim, s[i]) || s[i] == '$')
			break ;
		i++;
	}
	return (ft_substr(s, 0, i));
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
		if (is_char(*s, shell))
		{
			word = parse_string(s, shell);
			if (shell->in_quotes)
				token = new_token(STR, word, ft_strlen(word), shell->q_type);
			else
				token = new_token(STR, word, ft_strlen(word), DFAULT);
		}
		else if (*s == ' ')
		{
			word = ft_strdup(" ");
			if (shell->in_quotes)
				token = new_token(SPACE, word, 1, shell->q_type);
			else
				token = new_token(SPACE, word, 1, DFAULT);
		}
		else if (*s == '|' && !shell->in_quotes)
		{
				word = ft_strdup("|");
				token = new_token(PIPE, word, 1, DFAULT);
		}
		else if (*s == '>' && *(s + 1) == '>')
		{
			word = ft_strdup(">>");
			token = new_token(ARRED, word, 2, DFAULT);
		}
		else if (*s == '<' && *(s + 1) == '<')
		{
			word = ft_strdup("<<");
			token = new_token(ALRED, word, 2, DFAULT);
		}
		else if (*s == '>' && !shell->in_quotes)
		{
			word = ft_strdup(">");
			token = new_token(RRED, word, 1, DFAULT);
		}
		else if (*s == '<' && !shell->in_quotes)
		{
			word = ft_strdup("<");
			token = new_token(LRED, word, 1, DFAULT);
		}
		else if (*s == '$')
		{
			if (!*(s + 1) || is_delim(*(s + 1), shell))
				word = ft_strdup("$");
			else
				word = parse_var(s, shell);
			if (shell->in_quotes)
				token = new_token(VAR, word, ft_strlen(word), shell->q_type);
			else
				token = new_token(VAR, word, ft_strlen(word), DFAULT);
		}
		else if (*s == '\"')
		{
			word = ft_strdup("\"");
			token = new_token(DQUOTES, word, 1, DFAULT);
			shell->in_quotes = !shell->in_quotes;
			shell->q_type = INDQOUTES;
		}
		else if (*s == '\'')
		{
			word = ft_strdup("\'");
			token = new_token(SQUOTES, word, 1, DFAULT);
			shell->in_quotes = !shell->in_quotes;
			shell->q_type = INSQOUTES;
		}
		append_token(&shell->tokens, token);
		s += ft_strlen(word);
	}
}
