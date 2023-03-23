#include "../../includes/pipex.h"

void set_num_pipe(t_parse *p, int *num_read, int *num_write, int num_proc)
{
	if (num_proc != 0)
		*num_read = (num_proc - 1) * 2;
	else
		*num_read = -1;
	if (num_proc != p->count - 1)
		*num_write = 1 + 2 * num_proc;
	else
		*num_write = -1;
}

int	link_stdin(t_parse *p, int num_read)
{
	if (num_read >= 0)
	{
		if (dup2(p->pipes_fd[num_read], 0) == -1)
		{
			close(p->pipes_fd[num_read]);
			free(p->pipes_fd);
			return (0);
		}
		close(p->pipes_fd[num_read]);
	}
	return (1);
}

int	link_stdout(t_parse *p, int num_write)
{
	if (num_write >= 0)
	{
		if (dup2(p->pipes_fd[num_write], 1) == -1)
		{
			close(p->pipes_fd[num_write]);
			free(p->pipes_fd);
			return (0);
		}
		close(p->pipes_fd[num_write]);
	}
	return (1);
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
