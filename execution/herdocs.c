/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdocs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ou <abdel-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 13:04:15 by abdel-ou          #+#    #+#             */
/*   Updated: 2023/09/30 13:31:20 by abdel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_line_fd(t_shell *shell, int fd, char *str)
{
	char	*var_name;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
		{
			ft_putnbr_fd(g_exit_status, fd);
			i += 2;
		}
		if (str[i] == '$' && str[i + 1])
		{
			var_name = get_var(str + i + 1, shell);
			ft_putstr_fd(get_env(shell->env, var_name), fd);
			i += ft_strlen(var_name);
		}
		else
			ft_putchar_fd(str[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}

void	herdocs_condtion(t_shell *shell, int i, char *delimiter, int tmp1)
{
	while (shell->ready_commands[i].herdocs)
	{
		delimiter = readline("> ");
		if (!delimiter)
			break ;
		if (ft_strcmp(shell->ready_commands[i].herdocs->file, delimiter) == 0)
			break ;
		if (shell->ready_commands[i].herdocs->expand_herdoc)
			ft_print_line_fd(shell, tmp1, delimiter);
		else
		{
			ft_putstr_fd(delimiter, tmp1);
			ft_putchar_fd('\n', tmp1);
		}
	}
}

void	herdocs(t_shell *shell, int i)
{
	char	*delimiter;
	int		tmp1;
	int		tmp2;

	delimiter = NULL;
	unlink("/tmp/tmpp");
	tmp1 = open("/tmp/tmpp", O_APPEND | O_WRONLY | O_CREAT, 0777);
	rl_catch_signals = 1;
	herdocs_condtion(shell, i, delimiter, tmp1);
	shell->ready_commands[i].herdocs = shell->ready_commands[i].herdocs->next;
	if (shell->ready_commands[i].herdocs)
		herdocs(shell, i);
	close(tmp1);
	tmp2 = open("/tmp/tmpp", O_RDONLY);
	unlink("/tmp/tmpp");
	if (shell->ready_commands[i].cmd)
		dup2(tmp2, 0);
	close(tmp2);
	rl_catch_signals = 0;
}
