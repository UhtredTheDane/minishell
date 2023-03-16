/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:09:09 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/16 17:51:33 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../includes/main.h"
#include "../includes/envp.h"
/*
int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*in_put;
	t_parse *p;
	t_dico *envp_dico;
	char **mini_envp;

	if (argc < 1 || argc > 1)
		return (1);
	argv = (char **)argv;
	prompt = ">$";
	envp_dico = create_dico(envp);
	if (!envp_dico)
		return (1);
	if (!init_all_signal())
		return (1);
	while (1)
	{
		in_put = readline(prompt);
		if (in_put)
		{
			p = parsing(in_put);
			p->envp = create_envp_tab(envp_dico); 
			if (!p)
			{
				printf("parsing return is NULL\n");
				return (1);
			}
			add_history(in_put);
			if (!execute(p))
				free(in_put);
			free(in_put);
		}
		else
			exit(0);
	}
	rl_clear_history();
	return (0);
}*/

int main(int argc,char**argv,char **envp)
{
	t_parse *p;
	t_dico *envp_dico;
	char *tmp;
	
	envp_dico = create_dico(envp);
	if(argc  == 2)
	{
		//printf("  INPUT : %s\n",argv[1]);
		tmp = malloc(sizeof(char)*ft_strlen(argv[1]) + 1);
		ft_strlcat(tmp,argv[1],ft_strlen(argv[1]) + 1);
		printf("tmp : %s\n",tmp);
		p = parsing(tmp);
		if(!p)
		{
			printf("arg is not valid for some reasons");	
			return(0);
		}

		p->envp = create_envp_tab(envp_dico); 
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
}
