/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:59:28 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/27 05:12:38 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

int is_cd(t_cmd *cmd)
{
    if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
        return (1);
    return (0);
}

char *init_path(t_envp *envp, t_cmd *cmd)
{
    char *home;

    home = get_value(envp, "HOME");
    if (!home)
        return (cmd->cmd[1]);
    if (!cmd->cmd[1])
        return (home);
	else if (!cmd->cmd[2])
        return (replace_home(cmd, home));
    printf("minishell: cd: too many arguments\n");
    return (NULL);
}

int check_path(const char *path)
{
    struct stat buf;

    	if (lstat(path, &buf) == -1)
	{
        	printf("minishell: cd: %s No such file or directory\n", path);
		return (0);
	}
    	if (!S_ISDIR(buf.st_mode))
    	{
        	 printf("minishell: cd: %s Not a directory\n", path);
        	return (0);
    	}
    	return (1);
}

int update_env(t_envp *envp)
{
    char    *old_pwd;
    char    *new_pwd;
    char    *pwd;
   
    pwd = get_value(envp, "PWD");
    if (!pwd)
    {
	    old_pwd = env_with_no_pwd();
	    if (!old_pwd)
        	return (0);
    }
    else
    {
        if(!env_with_pwd(envp, pwd, &new_pwd, &old_pwd))
        {
            if (old_pwd)
                free(old_pwd);
            return (0);
        }
    }
    if (!set_value(envp, "OLDPWD", old_pwd))
	    free(old_pwd);
    return (1);
}

int builtin_cd(t_envp *envp, t_cmd *cmd)
{
    char *path;

    path = init_path(envp, cmd);
    if (!path)
        return (1);
    if (!check_path(path))
        return (1);
    if (chdir(path) == -1)
    {
        perror("cd");
        return (1);
    }
    if (!update_env(envp))
        printf("Probleme lors de l'update de l'environnement.\n");
    return (0);
}
