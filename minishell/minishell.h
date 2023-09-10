/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelmajid <abdelmajid@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 09:10:07 by abdelmajid        #+#    #+#             */
/*   Updated: 2023/09/10 13:42:39 by abdelmajid       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

char* getCommandPath(const char* command);
char ***to3d_arr(char *str);
char	**ft_splitt(char const *s, char c);
void execline(char ***cmd , char **env);

#endif

