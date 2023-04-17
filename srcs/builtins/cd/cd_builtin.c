/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:59:28 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/17 19:44:16 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

int	is_cd(t_cmd *cmd)
{
	size_t	size;

	size = ft_strlen(cmd->cmd[0]);
	if (size < 2)
		size = 2;
	if (ft_strncmp(cmd->cmd[0], "cd", size) == 0)
		return (1);
	return (0);
}

char	*init_path(t_parse *p, t_envp *envp, t_cmd *cmd)
{
	char	*home;
	char	*default_folder;
	char 	*old_pwd;
	char	*error;

	home = get_value(envp, "HOME");
	if (!home)
		default_folder = ft_strdup("HOME");
	else
		default_folder = ft_strdup(home);
	if (!cmd->cmd[1])
		return (default_folder);
	else if (!cmd->cmd[2])
	{
		if (ft_strlen(cmd->cmd[1]) == 1 && cmd->cmd[1][0] == '-')
		{
			free(default_folder);
			old_pwd = get_value(envp, "OLDPWD");
			if (old_pwd)
				return (ft_strdup(old_pwd));
			else
			{
				printf("OLDPWD is not present\n");
				return (NULL);
			}
		}
		return (replace_home(cmd, default_folder));
	}
	error = "too many arguments\n";
	write(p->default_out, "cd: ", 4);
	write(p->default_out, error, ft_strlen(error));
	free(default_folder);
	return (NULL);
}

int	check_path(t_parse *p, const char *path)
{
	struct stat	buf;
	char	*error;
	
	if (lstat(path, &buf) == -1 || path[0] == '-')
	{
		error = ft_strjoin(path, " No such file or directory\n");
		write(p->default_out, "cd: ", 4);
		write(p->default_out, error, ft_strlen(error));
		free(error);
		return (0);
	}
	if (!S_ISDIR(buf.st_mode))
	{
		error = ft_strjoin(path, " Not a directory\n");
		write(p->default_out, "cd: ", 4);
		write(p->default_out, error, ft_strlen(error));
		free(error);
		return (0);
	}
	return (1);
}

int	update_env(t_parse *p)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*pwd;

	pwd = get_value(p->envp, "PWD");
	if (!pwd)
	{
		old_pwd = env_with_no_pwd();
		if (!old_pwd)
			return (0);
	}
	else
	{
		if (!env_with_pwd(p, pwd, &new_pwd, &old_pwd))
		{
			if (old_pwd)
				free(old_pwd);
			return (0);
		}
	}
	if (!add_new_entries(p->envp, ft_strdup("OLDPWD"), old_pwd))
		free(old_pwd);
	return (1);
}

int	builtin_cd(t_parse *p, t_envp *envp, t_cmd *cmd)
{
	char	*path;

	path = init_path(p, envp, cmd);
	if (!path)
		return (1);
	if (!check_path(p, path))
	{
		free(path);
		return (1);
	}
	if (chdir(path) == -1)
	{
		perror("cd");
		free(path);
		return (1);
	}
	free(path);
	if (!update_env(p))
		return (1);
	return (0);
}
