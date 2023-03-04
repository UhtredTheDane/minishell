#include "../includes/pipex.h"

char	**make_cmd(char *one_string_cmd, char **envp)
{
	char	**cmd;
	char	*tempo_cmd;
	size_t	i;

	cmd = ft_split(one_string_cmd, ' ');
	if (!cmd)
		return (NULL);
	cmd[0] = format_string(cmd);
	if (!cmd[0])
		return (NULL);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		++i;
	tempo_cmd = find_path(envp, cmd, i);
	if (!tempo_cmd)
		return (NULL);
	cmd[0] = tempo_cmd;
	return (cmd);
}

char **search_cmd(t_config *config, char *input_cmd, int num_read, int num_write)
{
	char	**cmd;

	cmd = make_cmd(input_cmd, config->envp);
	if (!cmd)
	{
		if (num_write)
			close(config->pipes_fd[num_write]);
		if (num_read)
			close(config->pipes_fd[num_read]);
		free(input_cmd);
		free(config->pipes_fd);
		return (NULL);
	}
	return (cmd);
}

void manager(t_config *config, char *input_cmd, int num_proc)
{
	char	**cmd;
	int num_read;
	int num_write;

	set_num_pipe(config, &num_read, &num_write, num_proc);
	close_useless_pipes(config, num_read, num_write);
	cmd = search_cmd(config, input_cmd, num_read, num_write);
	if (!cmd)
		exit(1);
	if (!link_stdin(config, num_read))
		exit(2);
	if (!link_stdout(config, num_write))
		exit(3);
	execve(cmd[0], cmd, envp);
	free(input_cmd);
	free(config->pipes_fd);
	exit(4);
}

void	run_pipe(t_config *config, char **cmds)
{
	size_t	i;
	pid_t pid;

	i = 0;
	while (i < config->pipes_nb + 1)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Probleme fork");
			close_all_pipes(config);
			free(config->pipes_fd);
			exit(0);
		}
		else if (pid == 0)
			manager(config, cmds[i], i);
		++i;
	}
	close_all_pipes(config);
	waiting_all_sons(config->pipes_nb + 1);
}


int	execute(char *in_put, char **envp)
{
	t_config config;
	char	**cmds;
	
	cmds = ft_split(in_put, '|');
	if (!cmds)
	{
		printf("Erreur ft_split |\n");
		return (0);
	}
	if (!init_config(&config, envp))
	{
		clean_2d_tab(cmds);
		return (0);
	}
	run_pipe(cmds, envp, pipes_fd, pipes_nb);
	clean_2d_tab(cmds);
	free(config->pipes_fd);
	return (1);
}
