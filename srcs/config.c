int    init_config(t_config *config, char **envp)
{
    config->pipes_nb = count_pipes(in_put);
    config->pipes_fd = malloc(sizeof(int) * config->pipes_nb * 2);
	if (!config->pipes_fd)
		return (0);
    
}