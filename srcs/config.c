#include "../includes/pipex.h"

int    init_config(t_config *config, char **envp)
{
    size_t i;

    config->pipes_nb = count_pipes(in_put);
    config->pipes_fd = malloc(sizeof(int) * config->pipes_nb * 2);
	if (!config->pipes_fd)
		return (0);
	i = 0;
	while (i < config->pipes_nb * 2)
	{
		if (pipe(config->pipes_fd + i) == -1)
		{
			config->pipes_nb = i / 2;
            close_all_pipes(config);
            free(config->pipes_fd);
			return (0);
		}
		i += 2;
	}
	return (1);
}

void	close_useless_pipes(t_config *config, int num_read, int num_write)
{
	int i;

	i = 0;
	while (i < config->pipes_nb * 2)
	{
		if (i != num_read && i != num_write)
			close(config->pipes_fd[i]);
		++i;
	}
}

void close_all_pipes(t_config *config)
{
	int i;

	i = 0;
	while (i < config->pipes_nb * 2)
	{
		close(config->pipes_fd[i]);
		++i;
	}
}