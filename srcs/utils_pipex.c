#include "../includes/pipex.h"

void	clean_2d_tab(char **tab_2d)
{
	size_t	i;

	i = 0;
	while (tab_2d[i])
	{
		if (tab_2d[i])
			free(tab_2d[i]);
		++i;
	}
	free(tab_2d);
}

char	*format_string(char **cmd)
{
	char	*temp;

	temp = ft_strjoin("/", cmd[0]);
	if (!temp)
	{
		clean_2d_tab(cmd);
		return (NULL);
	}
	free(cmd[0]);
	return (temp);
}

char	*find_path(char **envp, char **cmd, size_t i)
{
	char	*temp;

	temp = get_path(envp[i] + 5, cmd[0]);
	if (!temp)
	{
		clean_2d_tab(cmd);
		return (NULL);
	}
	free(cmd[0]);
	return (temp);
}

char	*test_path(char **all_paths, char *cmd_0)
{
	size_t	i;
	char	*good_path;

	i = 0;
	while (all_paths[i])
	{
		good_path = ft_strjoin(all_paths[i], cmd_0);
		if (!good_path)
			return (NULL);
		if (access(good_path, F_OK) == 0)
			return (good_path);
		++i;
		free(good_path);
	}
	return (NULL);
}

char	*get_path(char *path, char *cmd_0)
{
	char	**all_paths;
	char	*cmd_path;

	all_paths = ft_split(path, ':');
	if (!all_paths)
		return (NULL);
	cmd_path = test_path(all_paths, cmd_0);
	clean_2d_tab(all_paths);
	return (cmd_path);
}