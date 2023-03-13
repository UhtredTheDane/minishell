/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:48:43 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/13 19:48:19 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
char *trim_dollard(t_cmd *cmd,int start,int end)
{
	int size;
	char *tmp;
	int i;
	size =end -start;
	 	
	i = 0;
	tmp = malloc(size + 1);
	if(!tmp)
		return(NULL);
	while(i <size)
	{
		tmp[i] = cmd->s[start + i];
		i++;
	}
	tmp[i]='\0';
	return(tmp);
}
int fill_env(t_cmd *cmd,t_dico *envp, int i)
{
	int op;	
	char *value;
	char *tmp;
	op = i;
	i++;
	if(cmd->s[i] && cmd->s[i] == '?')
	{	
		value =getvalue(envp,"?");
		i++;
	}
	else
	{
		if(is_special(cmd->s[i]))
			return(1);
		while(cmd->s[i] && !is_special(cmd->s[i]))
			i++;
		value = trim_dollard(cmd,op,i);
	}
	cmd->s[op]='\0';	
	tmp = ft_strjoin(cmd->s,value);
	tmp = ft_strjoin(tmp,cmd->s[i]);
	cmd->s = tmp;	
	return(1);
}
