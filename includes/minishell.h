/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:34:46 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/18 09:53:58 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <dirent.h>
# include "signal.h"

int	g_exit_status;

typedef enum e_state
{
	INDQOUTES,
	INSQOUTES,
	DFAULT,
}	t_state;

typedef enum e_toketype
{
	PIPE,
	_SPACE,
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

typedef struct s_redirec
{
	char				*file;
	t_tokentype			type;
	struct s_redirec	*next;
}	t_redirec;

typedef struct s_command
{
	char		*cmd;
	char		**args;
	t_redirec	*redirections;
}	t_command;

typedef struct s_shell
{
	int			in_quotes;
	int			q_type;
	t_token		*tokens;
	t_env		*env;
	char		**cmd_table;
	int			cmd_count;
	int			exit_status;
	t_token		**commands;
	t_command	*ready_commands;
	char		cwd[1024];
}	t_shell;
int		is_valid_echo_option(char *option);
void	print_final_command(t_command *command);
void	split_cmds(t_shell	*shell);
void	execute_builtins2(t_shell *shell, t_command command);
int		check_valid_variable(char *var);
int		is_valid_exit_status(char *status);
//prsing utilities
int		is_char(int c, t_shell *shell);
int		is_delim(int c, t_shell *shell);
char	*get_word(char *s, t_shell *shell);
char	*get_var(char *s, t_shell *shell);
void	set_value(char **w, t_token **token, char *value, t_tokentype tt);
void	lexer(t_shell *shell, char *s);
void	expand(t_shell *shell);
int		is_redirection(t_token *token);
t_token	*remove_space_from_tokens(t_token *tokens);

//token methods
t_token	*new_token(t_tokentype type, char *content, int length, t_state state);
void	append_token(t_token **tokens, t_token *new);
void	print_tokens(t_token *tokens);
t_token	*get_last_token(t_token *tokens);
int		get_list_size(t_token *head);
void	print_echo(t_token *tmp);
void	delete_token(t_token **head, char *content);

int		has_error(t_shell *shell);

//env utils
t_env	*new_env(char *key, char *value);
int		push_env(t_env **env, char *key, char *value);
void	env_to_list(t_shell *shell, char **env);
void	print_env(t_env *head, int flag);
char	*get_env(t_env *env, char *key);
int		set_env(t_env **env, char *key, char *value, int overrite);
int		unset_env(t_env **env, char *key);
char 	**env_to_array(t_env *env);
//builtins
void	execute_builtins(t_shell *shell, char **command);
//array utils
int		array_size(char **arr);
char	**append_to_array(char **arr, char *value);
char	**get_command_table(t_token *tokens);
void	print_cmd_table(char **args);

void	get_ready_commands(t_shell *shell);

//* builtins
void	ft_echo(t_shell *shell, char **command);
void	ft_export(t_shell *shell, char **command);
void	ft_env(t_shell *shell, char **command);
void	ft_pwd(t_shell *shell);
void	ft_chdir(t_shell *shell, char **command);
void	ft_unset(t_shell *shell, char **command);
void	ft_exit(t_shell *shell, char **command);

//*excution
char	*getCommandPath(t_env *env, const char* command);
char ***to3d_arr(t_shell *shell);
char	**ft_splitt(char const *s, char c);
void 	execline(t_shell *shell, char **env);
void execute_builtins_new(t_shell *shell, char **command);
int is_builtin(char *cmd);
int is_child_builtin(char *cmd);
char *get_full_path(t_env *env, char **tokens);
#endif