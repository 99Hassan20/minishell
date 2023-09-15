/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:15:37 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/15 08:48:52 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_char(int c, t_shell *shell)
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

int	is_delim(int c, t_shell *shell)
{
	return (!is_char(c, shell));
}

char	*get_word(char *s, t_shell *shell)
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

char	*get_var(char *s, t_shell *shell)
{
	int		i;
	char	*delim;

	i = 1;
	if (shell->in_quotes)
		delim = " \"'$";
	else
		delim = "| ><\"'$";
	if (s[i] == '$')
		return (ft_substr(s, 0, i + 1));
	if (s[i] == '?')
		return (ft_substr(s, 0, i + 1));
	if (ft_isdigit(s[i]))
		return (ft_substr(s, 0, i + 1));
	if (s[i] == '@')
		return (ft_substr(s, 0, i + 1));
	while (s[i])
	{
		if (ft_strchr(delim, s[i]) || (!ft_isalnum(s[i]) && s[i] != '_'))
			break ;
		i++;
	}
	return (ft_substr(s, 0, i));
}

void	set_value(char **w, t_token **token, char *value, t_tokentype tt)
{
	*w = ft_strdup(value);
	*token = new_token(tt, *w, ft_strlen(*w), DFAULT);
}
