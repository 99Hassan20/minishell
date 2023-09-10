/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelmajid <abdelmajid@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 18:45:33 by abdelmajid        #+#    #+#             */
/*   Updated: 2023/07/02 10:58:50 by abdelmajid       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

#define MAX_PATH_LENGTH 1024


char *ft_strpbrk(const char *s1, const char *s2)
{
	int i = 0;
	
	if (!s1 || !s2)
	{
		return (0);
	}
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

char* getCommandPath(const char* command) 
{
    char* commandPath = NULL;
    char* pathEnv = getenv("PATH");
    char* pathCopy = strdup(pathEnv);
    char* dir = strtok_custom(pathCopy, ":");

    while (dir != NULL) {
        char fullPath[MAX_PATH_LENGTH];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", dir, command);

        // Check if the command exists at the current path
        if (access(fullPath, X_OK) == 0) {
            commandPath = strdup(fullPath);
            break;
        }

        dir = strtok_custom(NULL, ":");
    }

    free(pathCopy);
    return commandPath;
}
