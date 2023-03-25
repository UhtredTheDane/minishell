/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:03:30 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/23 18:15:29 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int is_unset(t_cmd *cmd)
{ 

    if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
        return (1);
    return (0);
}

int dollar_in_str(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		++i;
	}
	return (0);
} 

/*
void    builtin_unset(t_parse *p, t_cmd *cmd)
{
    char *key;
    char *name_var;
    char *value_var;
    int dollar_pos;
    int i = 0;
    int size_name;
    int return_code;
    
    
    while dollar_in_str((p->s + i))
    {
        dollar_pos = skip_to_X(p->s, i, "$");
        dollar_pos += 1;
        i = dollar_pos;
        while (ft_isalnum(s[i]))
            ++i;
        size_name = i - dollar_pos;
        name_var = malloc(sizeof(char) * (size_name + 1));
        if (name_var)
        {
            ft_strlcpy(name_var, p->s + dollar_pos, size_name + 1)
            value_var = getenv(name_var);
            if (value_var)
            {
                return_code = 1;
            }
            else
                printf("ne rien faire");

        }
    }

    i = 0;
    while (cmd->cmd[i])
    {
        key = cmd->cmd[i];
        delete_key(envp, key);
    }


}
