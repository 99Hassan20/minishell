/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:09:59 by hoigag            #+#    #+#             */
/*   Updated: 2023/06/14 21:06:51 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_env(t_shell *shell)
{
	int	i;

	i = 1;
	while (shell->cmd_table[i])
	{
		if (ft_strcmp(shell->cmd_table[i], "env") != 0)
		{
			printf("env: %s: No such file or directory\n", shell->cmd_table[i]);
			return ;
		}
		i++;
	}
	print_env(shell->env, 1);
}

int	is_valid_echo_option(char *option)
{
	int	i;

	if (option[0] != '-')
		return (0);
	i = 1;
	if (!option[i])
		return (0);
	while (option[i] && option[i] == 'n')
		i++;
	if (!option[i])
		return (1);
	return (0);
}

static void	ft_echo(t_shell *shell)
{
	int		i;
	int		print_nl;

	i = 1;
	print_nl = 1;
	if (!shell->cmd_table[1])
	{
		printf("\n");
		return ;
	}
	while (shell->cmd_table[i] && is_valid_echo_option(shell->cmd_table[i]))
	{
		print_nl = 0;
		i++;
	}
	while (shell->cmd_table[i])
	{
		printf("%s", shell->cmd_table[i]);
		if (shell->cmd_table[i + 1])
			printf(" ");
		i++;
	}
	if (print_nl)
		printf("\n");
}

void	ft_pwd(t_shell *shell)
{
	if (getcwd(shell->cwd, sizeof(shell->cwd)))
		printf("%s\n", shell->cwd);
	else
		printf("pwd: error\n");
}

void	ft_chdir(t_shell *shell)
{
	char	*path;

	if (!shell->cmd_table[1])
		path = get_env(shell->env, "HOME");
	else
		path = shell->cmd_table[1];
	if (chdir(path) == -1)
		printf("minishell: cd: %s: No such file or directory\n", path);
}

int		check_valid_variable(char *var)
{
	int	i;

	if (var[0] != '_' && !ft_isalpha(var[0]))
		return (0);
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(t_shell *shell)
{
	int		i;
	char	**pair;

	i = 1;
	if (!shell->cmd_table[1])
	{
		print_env(shell->env, 2);
		return ;
	}
	while (shell->cmd_table[i])
	{
		if (!check_valid_variable(shell->cmd_table[i]))
			printf("minishell: export: `%s': not a valid identifier\n", shell->cmd_table[i]);
		pair = ft_split(shell->cmd_table[i], '=');
		// if (!pair[1])
		// 	pair[1] = "
		// printf("[%s][%s]\n", pair[0], pair[1]);
		set_env(&shell->env, pair[0], pair[1], 1);
		i++;
	}
}

void	execute_builtins(t_shell *shell)
{
	if (ft_strcmp(shell->cmd_table[0], "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(shell->cmd_table[0], "echo") == 0)
		ft_echo(shell);
	else if (ft_strcmp(shell->cmd_table[0], "pwd") == 0)
		ft_pwd(shell);
	else if (ft_strcmp(shell->cmd_table[0], "cd") == 0)
		ft_chdir(shell);
	else if (ft_strcmp(shell->cmd_table[0], "exit") == 0)
	{
		printf("exit\n");
		exit(0);
	}
	else if (ft_strcmp(shell->cmd_table[0], "export") == 0)
		ft_export(shell);
}
