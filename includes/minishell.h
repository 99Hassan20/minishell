/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ou <abdel-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:34:46 by hoigag            #+#    #+#             */
/*   Updated: 2023/10/02 13:01:25 by abdel-ou         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/wait.h>

int	g_exit_status;

typedef struct s_file_dis
{
	int		fdd;
	int		fd[2];
}	t_file_dis;

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
	int					expand_herdoc;
}	t_redirec;

typedef struct s_command
{
	char		*cmd;
	char		**args;
	t_redirec	*redirections;
	t_redirec	*herdocs;
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
	int			in_herdoc;
	char		*executable;
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
void	expand(t_shell *shell, int to_expand);
void	expand_var(t_shell *shell, t_token *tmp, t_token **new);
int		is_expandable(t_token *tmp, int to_expand);
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
t_token	*copy_tokens(t_token *cmd);

int		has_error(t_shell *shell);

//env utils
t_env	*new_env(char *key, char *value);
int		push_env(t_env **env, char *key, char *value);
void	env_to_list(t_shell *shell, char **env);
void	print_env(t_env *head, int flag);
char	*get_env(t_env *env, char *key);
int		set_env(t_env **env, char *key, char *value, int overrite);
int		unset_env(t_env **env, char *key);
char	**env_to_array(t_env *env);

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
void	execute_builtins(t_shell *shell, char **command);

//*excution
void	execline(t_shell *shell, char **env);
int		is_builtin(char *cmd);
int		is_child_builtin(char *cmd);
char	*get_full_path(t_env *env, char **tokens);
int		herdocs(t_shell *shell, int i);
char	*get_var(char *s, t_shell *shell);

//*redirections
void	add_redirection(t_token **new, t_token **tmp);
t_token	*remove_redirections(t_token *tokens);
void	append_redirec(t_redirec **head, char *file, int type, int exp);
char	**init_data(char **file_name, char **expand_herdoc);
void	set_file_name(t_token *tmp, char **file_name);

//*free
void	free_tokens(t_token *token);
void	free_token(t_token *token);
void	free_redirections(t_redirec **redirections);
void	free_commands(t_token **commands, int cmd_count);
void	full_free(t_shell *shell);
void	free_single_token(t_token **tokens);
char	*leak_free_join(char *s1, char *s2);
void	free_env(t_env *env);

//*printing
void	print_final_command(t_command *command);
void	print_all_ready_commands(t_shell *shell);

void	error_log(char *file_name);

void	ft_rred(t_shell *shell, int i);
void	ft_arred(t_shell *shell, int i);
void	ft_lred(t_shell *shell, int i);
void	redirection(t_shell *shell, int i);
void	ft_print_line_fd(t_shell *shell, int fd, char *str);
void	error_log(char *file_name);
int		is_relative_path(char *file);
void	execute_parent_builtin(t_shell *shell, char **cmd);
int		ft_check_dir(t_shell *shell, int *i);
int		run_redi_whiout_cmd(t_shell *shell, int *i);
int		ft_check_builtins_run(t_shell *shell, int *i);
#endif