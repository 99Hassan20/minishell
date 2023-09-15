/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 09:12:05 by abdelmajid        #+#    #+#             */
/*   Updated: 2023/09/15 08:48:52 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char** argv , char **env){
	(void)argc;

	(void)argv;
		
			char* buf;
	 char ***cmd;

	while (1) {
		buf = readline(">> ");
			
		cmd = to3d_arr(buf);


		if (strlen(buf) > 0) 
		{
			add_history(buf);
		}
		 execline(cmd,env);

		
	}
	return 0;
}


		
		
