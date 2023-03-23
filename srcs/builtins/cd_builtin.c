/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:59:28 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/23 18:14:12 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int is_cd(t_parse *p, t_cmd *cmd)
{
    if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
    {
        builtin_cd(p->envp, cmd->cmd[1]);
        return (1);
    }
    return (0);
}

int builtin_cd(t_envp *envp, const char *path)
{
    char    *old_pwd;
    char    *new_pwd;
    char    *pwd;
    size_t pwd_size;

    if (chdir(path) == -1)
    {
        perror("Erreur cd\n");
        return (0);
    }
    pwd = get_value(envp, "PWD");
    pwd_size = ft_strlen(pwd);
    old_pwd = malloc(sizeof(char) * (pwd_size + 1));
    if (!old_pwd)
        return (0);
    ft_strlcpy(old_pwd, pwd, pwd_size + 1);
    new_pwd = builtin_pwd();
    //seulement si existe
    set_value(envp, "OLDPWD", old_pwd);
    set_value(envp, "PWD", new_pwd);
    return (1);
}
