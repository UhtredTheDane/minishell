/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:48:36 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/15 16:02:31 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
int replace(char *s,int start,int end, char *rep)
{
	char *addr;
	int size;
	int i;

	i = 0;
	size = 0;
	addr = s;
	while(i <start &&s[i])
	{
		i++;
		size++;
	} 
	i = 0
	while(s[i + end])
		size++;
	size = size + ft_strlen(rep);
}

char *replace_double_quote(t_cmd *cmd,int i)
{
	int start_w;
	char *tmp;	

	i++;
	start_w = i;
	while(cmd->s[i] && cmd->s[i] != '\"')
		i++;
	tmp2 = ft_strjoin(tmp,tmp[start_w]);
	cmd->s = ft_strjoin();
}*/
