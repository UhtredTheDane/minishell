/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:09:09 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/06 00:56:07 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"
#include "../includes/envp.h"
#include "../includes/signals.h"
#include "../includes/parsing.h"

int cmd_return = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*in_put;
	t_parse *p;
	t_envp *envp_dico;

	if (argc < 1 || argc > 1)
		return (1);
	argv = (char **)argv;
	prompt = "Minishell :";
	envp_dico = create_shell_envp(envp);
	p = NULL;
	in_put = NULL;
	if (!envp_dico)
		return (1);
	if (!init_no_interactive_signals()) 
		return (1);
	while (1)
	{
		if(in_put)
			free(in_put);
		in_put = readline(prompt);
		if (in_put)
		{
			if(p)
				free_parse(p);
			p = parsing(in_put, envp_dico);
			if (!p)
				printf("parsing error\n");
			else
			{
				add_history(p->s);
				//			display_parse(p);	
				if(!replace_dollards(p,envp_dico))
				{
					printf("we can't replace some variable");
					return(0);
				}
				else
				{
					if (!execute(p))
						printf("Execution foiree\n");	
				}		
			}
		}
		else
		{		
			return (clean_exit(p,envp_dico));
		}
	}
	delete_dico(envp_dico);
	return(0);
}
/*
   int main(int argc,char**argv,char **envp)
   {
   t_parse *p;
   t_dico *envp_dico;
   char *tmp;

   envp_dico = create_dico(envp);
   if(argc  == 2)
   {
//printf("  INPUT : %s\n",argv[1]);
tmp = malloc(sizeof(char)*(ft_strlen(argv[1]) + 1));
ft_strlcpy(tmp,argv[1],ft_strlen(argv[1]) + 1);
p = parsing(tmp, envp_dico);
if(!p)
{
printf("arg is not valid for some reasons");	
return(0);
}

//		display_parse(p);
if(!replace_dollards(p,envp_dico))
{
printf("we can't replace some variable");
return(0);

}	
//		display_parse(p);
if(!edit_parsing(p))
{
printf("parsing has been cancel for some reasons");
return(0);
}
if(!split_cmd(p))
{
printf("split failed for some reason");
return(0);
}
else
{
display_parse(p);
//			free_parse(p);
return(1);
}
}
}*/
