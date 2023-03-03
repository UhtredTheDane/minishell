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