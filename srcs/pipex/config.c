#include "../includes/pipex.h"


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
