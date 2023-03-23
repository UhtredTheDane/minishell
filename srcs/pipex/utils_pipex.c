#include "../../includes/pipex.h"

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

void	close_useless_pipes(t_parse *p, int num_read, int num_write)
{
	int i;

	i = 0;
	while (i < (p->count - 1) * 2)
	{
		if (i != num_read && i != num_write)
			close(p->pipes_fd[i]);
		++i;
	}
}

void close_all_pipes(t_parse *p)
{
	int i;

	i = 0;
	while (i < (p->count - 1) * 2)
	{
		close(p->pipes_fd[i]);
		++i;
	}
}
