/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:50:57 by hoigag            #+#    #+#             */
/*   Updated: 2023/09/13 16:03:33 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *is_file_in_path(char *path, char *file)
{
	int i = 0;
	char *full_path;
	char **dirs;
	char *base;

	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	while (dirs[i])
	{
		base = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(base, file);
		free(base);
		if (access(full_path, F_OK) == 0)
		{
			ft_free_2d(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_2d(dirs);
	return (NULL);
}

char *get_full_path(t_env *env, char **cmd)
{
	char *path = get_env(env, "PATH");
	char *full_path = NULL;

    if (!cmd || !cmd[0] || !cmd[0][0])
        return (NULL);
	if (cmd[0][0] == '.' && cmd[0][1] == '/'
			&& access(cmd[0], F_OK) == 0
            && access(cmd[0], X_OK) == 0)
		full_path = ft_strdup(cmd[0]);
	else if (cmd[0][0] == '.'
			&& cmd[0][1] == '.' && cmd[0][1] == '.'
			&& access(cmd[0], F_OK) == 0
            && access(cmd[0], X_OK) == 0)
		full_path = ft_strdup(cmd[0]);
	else if (cmd[0][0] == '/' && access(cmd[0], F_OK) == 0
        && access(cmd[0], X_OK) == 0)
		full_path = ft_strdup(cmd[0]);
	else
	{
		if (!path)
		{
			free(full_path);
			return (NULL);
		}
		full_path = is_file_in_path(path, cmd[0]);
	}
	return (full_path);
}