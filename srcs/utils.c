#include "../includes/main.h"

size_t	count_pipes(char *in_put)
{
	size_t	i;
	size_t	pipes_nb;

	i = 0;
	pipes_nb = 0;
	while (in_put[i])
	{
		if (in_put[i] == '|')
			++pipes_nb;
		++i;
	}
	return (pipes_nb);
}

void waiting_all_sons(size_t nb_sons)
{
	size_t	i;

	i = 0;
	while (i < nb_sons)
	{
		waitpid(-1, NULL, 0);
		++i;
	}
}

void set_num_pipe(t_config *config, int *num_read, int *num_write, int num_proc)
{
	if (num_proc != 0)
		*num_read = (num_proc - 1) * 2;
	else
		*num_read = -1;
	if (num_proc != config->pipes_nb)
		*num_write = 1 + 2 * num_proc;
	else
		*num_write = -1;
}

int	link_stdin(t_config *config, int num_read)
{
	if (num_read >= 0)
	{
		if (dup2(config->pipes_fd[num_read], 0) == -1)
		{
			close(config->pipes_fd[num_read]);
			free(input_cmd);
			free(config->pipes_fd);
			return (0);
		}
		close(config->pipes_fd[num_read]);
	}
	return (1);
}

int	link_stdout(t_config *config, int num_write)
{
	if (num_write >= 0)
	{
		if (dup2(config->pipes_fd[num_write], 1) == -1)
		{
			close(config->pipes_fd[num_write]);
			free(input_cmd);
			free(config->pipes_fd);
			return (0);
		}
		close(config->pipes_fd[num_write]);
	}
	return (1);
}