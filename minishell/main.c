/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelmajid <abdelmajid@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 09:12:05 by abdelmajid        #+#    #+#             */
/*   Updated: 2023/09/10 13:19:25 by abdelmajid       ###   ########.fr       */
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


    
    
