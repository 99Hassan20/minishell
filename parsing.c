/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:10:03 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/03 17:17:23 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_char(int c)
{
	return (!ft_strchr(SPECIALS, c));
}

static char	*is_delim(int c)
{
	return (ft_strchr(DELIMITERS, c));
}

static char	*parse_string(char *s)
{
	int	i;

	i = 0;
	while (s[i] && !is_delim(s[i]) && s[i] != '\"')
	{
		if (s[i] == '$' && (is_char(s[i + 1]) || s[i + 1] == '$'))
			break ;
		i++;
	}
	return (ft_substr(s, 0, i));
}

static char	*parse_var(char *s)
{
	int	i;

	i = 1;
	if (s[i] == '$')
		return (ft_substr(s, 0, i + 1));
	while (s[i])
	{
		if (is_delim(s[i]) || s[i] == '$')
			break ;
		i++;
	}
	return (ft_substr(s, 0, i));
}

// static char	*parse_double_quotes(t_shell *shell, char *s)
// {
// 	int		i;
// 	char	*word;
// 	t_token	*token;

// 	i = 1;
// 	while (s[i] && s[i] != '\"')
// 	{
// 		if (is_char(*s))
// 		{
// 			word = parse_string(s);
// 			token = new_token(STR, word, ft_strlen(word), DQUOTES);
// 		}
// 	}
// 	return (ft_substr(s, 0, i + 1));
// }

void	lexer(t_shell *shell, char *s)
{
	char	*word;
	t_token	*token;

	shell->tokens = NULL;
	while (*s)
	{
		if (is_char(*s))
		{
			word = parse_string(s);
			if (shell->qstate)
				token = new_token(STR, word, ft_strlen(word), INDQOUTES);
			else
				token = new_token(STR, word, ft_strlen(word), DFAULT);
		}
		else if (*s == ' ')
		{
			word = ft_strdup(" ");
			if (shell->qstate)
				token = new_token(SPACE, word, 1, INDQOUTES);
			else
				token = new_token(SPACE, word, 1, DFAULT);
		}
		else if (*s == '|')
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
		else if (*s == '>')
		{
			word = ft_strdup(">");
			token = new_token(RRED, word, 1, DFAULT);
		}
		else if (*s == '<')
		{
			word = ft_strdup("<");
			token = new_token(LRED, word, 1, DFAULT);
		}
		else if (*s == '$')
		{
			if (!*(s + 1) || is_delim(*(s + 1)))
				word = ft_strdup("$");
			else
				word = parse_var(s);
			token = new_token(VAR, word, ft_strlen(word), DFAULT);
		}
		else if (*s == '\"')
		{
			word = ft_strdup("\"");
			token = new_token(DQUOTES, word, 1, INDQOUTES);
			shell->qstate = !shell->qstate;
		}
		append_token(&shell->tokens, token);
		s += ft_strlen(word);
	}
}
