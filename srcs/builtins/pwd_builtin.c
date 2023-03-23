/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:02:46 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/23 18:15:15 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

char *builtin_pwd()
{
    char    *buffer;

    buffer = ft_calloc(PATH_MAX + 1, sizeof(char));
    if (!buffer)
        return (NULL);
    if (!getcwd(buffer, PATH_MAX))
    {
        perror("Erreur getcwd\n");
        free(buffer);
        return (NULL);
    }
    return (buffer);
}

int is_pwd(t_cmd *cmd)
{
    if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0)
    {
        printf("%s\n", builtin_pwd());
        return (1);
    }
    return (0);
}
