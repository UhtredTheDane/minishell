#ifndef CONFIG_H
#define CONFIG_H

typedef struct s_config
{
	char **envp;
    int pipes_nb;
    int *pipes_fd;
}	t_config;

void	close_useless_pipes(t_parse *p, int num_read, int num_write);
void close_all_pipes(t_parse *p);
#endif
