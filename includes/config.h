#ifndef CONFIG_H
#define CONFIG_H

typedef struct s_config
{
	char **envp;
    int pipes_nb;
    int *pipes_fd;
}	t_config;

int    init_config(t_config *config, char *in_put, char **envp);
void	close_useless_pipes(t_config *config, int num_read, int num_write);
void close_all_pipes(t_config *config);
#endif
