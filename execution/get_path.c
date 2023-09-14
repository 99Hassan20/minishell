/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 18:45:33 by abdelmajid        #+#    #+#             */
/*   Updated: 2023/09/13 19:32:24 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

#define MAX_PATH_LENGTH 1024

char *ft_strpbrk(const char *s1, const char *s2)
{
	int i = 0;
	
	if (!s1 || !s2)
		return (0);
	while(*s1)
	{
		i = 0;
	   	while(s2[i])
		{
			if(*s1 == s2[i])
				return (char *) s1;
			i++;
		}
		s1++;	
	}
	return (0);
}

char* strtok_custom(char* str, const char* delimiters) {
    static char* token = NULL;
    if (str != NULL) {
        token = str;
    } else if (token == NULL) {
        return NULL;
    }

    char* delimiter_ptr = ft_strpbrk(token, delimiters);
    if (delimiter_ptr != NULL) {
        *delimiter_ptr = '\0';
        char* result = token;
        token = delimiter_ptr + 1;
        return result;
    } else {
        char* result = token;
        token = NULL;
        return result;
    }
}

char* getCommandPath(t_env *env, const char* command) 
{
    char* commandPath = NULL;
    char* pathEnv = get_env(env, "PATH");
    char* pathCopy = ft_strdup(pathEnv);
    char* dir = strtok_custom(pathCopy, ":");

    if (!command || !command[0])
        return (NULL);
    while (dir != NULL) {
        char fullPath[MAX_PATH_LENGTH];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", dir, command);

        // Check if the command exists at the current path
        if (access(fullPath, X_OK) == 0) {
            commandPath = ft_strdup(fullPath);
            break;
        }
        dir = strtok_custom(NULL, ":");
    }

    free(pathCopy);
    return commandPath;
}
