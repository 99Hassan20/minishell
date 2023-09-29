char	*get_file_name(t_token **tokens)
{
	// printf("int the second funciton\n");
	char   *file_name;

	file_name = "";
	if ((*tokens)->type == _SPACE)
		(*tokens) = (*tokens)->next;
	while ((*tokens) && (*tokens)->type != _SPACE)
	{

		// printf("in second loop: %s\n", (*tokens)->content);
		if ((*tokens)->type != DQUOTES && (*tokens)->type != SQUOTES)
			file_name = ft_strjoin(file_name, (*tokens)->content);
		*tokens = (*tokens)->next;
	}
	// printf("file_name: %s\n", file_name);
	// printf("out the second funciton\n");
	return (file_name);
}

void set_redirections(t_token *tokens, t_redirec **redirs, t_redirec **herdocs)
{
	// t_token *tmp;

	// tmp = tokens;
	// print_tokens(tokens);
	// printf("in set redirections\n");
	while (tokens)
	{
		// printf("content: %s\n", tokens->content);
		// 	printf("delimiter: %s\n", get_file_name(&tokens->next));
			// get_file_name(&tokens->next);
		if (tokens->type == ALRED && tokens->next)
			append_redirec(herdocs,
				get_file_name(&tokens->next), tokens->type);
		else if (is_redirection(tokens) && tokens->next)
			append_redirec(redirs,
				get_file_name(&tokens->next), tokens->type);
		// 	printf("file_name: %s\n", get_file_name(&tokens->next));
		tokens = tokens->next;
	}
	// printf("out set redirections\n");

}


t_command	get_final_command(t_token *cmd)
{
	t_command	command;
	// t_token		*tmp;
	// t_token		*nospace;

	// nospace = remove_space_from_tokens(cmd);
	// tmp = nospace;
	if (cmd && cmd->type == _SPACE)
		cmd = cmd->next;
	command.redirections = NULL;
	command.herdocs = NULL;
	set_redirections(cmd, &command.redirections, &command.herdocs);
	remove_all_redir(&cmd);
	command.args = get_command_table(cmd);
	if (command.args && command.args[0])
		command.cmd = command.args[0];
	else
		command.cmd = NULL;
	return (command);
}

void ft_print_line_fd(t_shell *shell, int fd, char *str)
// {
// 	int i = 0;
// 	char *var_name;

// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1])
// 		{
// 			var_name = get_var(str + i + 1, shell);
// 			ft_putstr_fd(get_env(shell->env, var_name), fd);
// 			i += ft_strlen(var_name);
// 		}
// 		else
// 			ft_putchar_fd(str[i], fd);
// 		i++;
// 	}
// 	ft_putchar_fd('\n', fd);
// }

		if (shell->ready_commands[i].herdocs->expand_herdoc)
			ft_print_line_fd(shell, tmp1, delimiter);
		else
		{
			ft_putstr_fd(delimiter, tmp1);
			ft_putchar_fd('\n', tmp1);
		}