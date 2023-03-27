/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:59:28 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/25 19:02:28 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int is_cd(t_cmd *cmd)
{
    if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
        return (1);
    return (0);
}

char *init_path(t_envp *envp, t_cmd *cmd)
{
    char *default_folder;
    char  *home_replace;

    default_folder = NULL;
    home_replace = NULL;
    if (!cmd->cmd[2])
    {
        if (!cmd->cmd[1] || (cmd->cmd[1][0] = '~'))
        {
            default_folder = get_value(envp, "HOME");
            if (!default_folder)
                return (cmd->cmd[1])
            if (cmd->cmd[1] && cmd->cmd[1][0] = '~' && ft_strlen(cmd->cmd[1]) != 1)
            {
                home_replace = ft_strjoin(default_folder, cmd->cmd[1][1]);
                if(!home_replace)
                    return (cmd->cmd[1]);
                return (home_replace);
            }
            return (default_folder);
        }
        else
            return (cmd->cmd[1]);
    }
    printf("minishell: cd: too many arguments\n");
    return (NULL);
}

int check_path(const char *path)
{
    struct stat buf;

    if (lstat(path, &buf) == -1)
        return (0);
    if (!S_ISDIR(buf.st_mode))
    {
         printf("minishell: cd: not a directory: %s\n", path);
        return (0);
    }
    return (1);
}

char  *env_with_no_pwd()
{
    char *old_pwd;

    old_pwd = malloc(sizeof(char));
	if (!old_pwd)
        return (NULL);
	old_pwd[0] = '\0';
    return (old_pwd);
}

int env_with_pwd(t_envp *envp, char *pwd, char **new_pwd, char **old_pwd)
{
	size_t pwd_size;

	pwd_size = ft_strlen(pwd);
    *old_pwd = malloc(sizeof(char) * (pwd_size + 1));
    if (!(*old_pwd))
        return (0);
    ft_strlcpy(*old_pwd, pwd, pwd_size + 1);
    *new_pwd = builtin_pwd();
	if (*new_pwd)
    	set_value(envp, "PWD", *new_pwd);
    else
        return (0);
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

    path = init_path(cmd);
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
