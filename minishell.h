/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:34:46 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/13 20:30:11 by hoigag           ###   ########.fr       */
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

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
	t_env	*env;
	char	**cmd_table;
	char	*last_dir;
	char	cwd[1024];
}	t_shell;

//prsing utilities
int		is_char(int c, t_shell *shell);
int		is_delim(int c, t_shell *shell);
char	*get_word(char *s, t_shell *shell);
char	*get_var(char *s, t_shell *shell);
void	set_value(char **w, t_token **token, char *value, t_tokentype tt);
void	lexer(t_shell *shell, char *s);
void	expand(t_shell *shell);

//token methods
t_token	*new_token(t_tokentype type, char *content, int length, t_state state);
void	append_token(t_token **tokens, t_token *new);
void	print_tokens(t_token *tokens);
t_token	*get_last_token(t_token *tokens);
int		get_list_size(t_token *head);
void	print_echo(t_token *tmp);

int		has_error(t_shell *shell);

//env utils
t_env	*new_env(char *key, char *value);
int		push_env(t_env **env, char *key, char *value);
void	env_to_list(t_shell *shell, char **env);
void	print_env(t_env *head);
char	*get_env(t_env *env, char *key);
int		set_env(t_env **env, char *key, char *value, int overrite);
int		unset_env(t_env **env, char *key);
//builtins
void	execute_builtins(t_shell *shell);
//array utils
int		array_size(char **arr);
char	**append_to_array(char **arr, char *value);
void	get_command_table(t_shell *shell);
void	print_cmd_table(t_shell *shell);
#endif