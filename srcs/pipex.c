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

void	close_useless_pipes(int	*pipes_fd, int num_proc, int nb_procs)
{
	int num_read;
	int num_write;
	int i;

	num_read = -1;
	if (num_proc)
		num_read = (num_proc - 1) * 2;
	num_write = -1;
	if (num_proc != nb_procs - 1)
		num_write = 1 + 2 * num_proc;
	i = 0;
	while (i < (nb_procs - 1) * 2)
	{
		if (i != num_read && i != num_write)
			close(pipes_fd[i]);
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

void manager(t_config *config, char *input_cmd, int num_proc, int nb_procs)
{
	char	**cmd;
	int num_read;
	int num_write;

	close_useless_pipes(pipes_fd, num_proc, nb_procs);
	num_read = -1;
	if (num_proc != 0)
		num_read = (num_proc - 1) * 2;
	num_write = -1;
	if (num_proc != nb_procs - 1)
		num_write = 1 + 2 * num_proc;
	cmd = make_cmd(input_cmd, envp);
	if (!cmd)
	{
		if (num_write)
			close(pipes_fd[num_write]);
		if (num_read)
			close(pipes_fd[num_read]);
		free(input_cmd);
		exit(1);
	}
	if (num_read >= 0)
	{
		if (dup2(pipes_fd[num_read], 0) == -1)
		{
			close(pipes_fd[num_read]);
			free(input_cmd);
			exit(2);
		}
		close(pipes_fd[num_read]);
	}
	if (num_write >= 0)
	{
		if (dup2(pipes_fd[num_write], 1) == -1)
		{
			close(pipes_fd[num_write]);
			free(input_cmd);
			exit(2);
		}
		close(pipes_fd[num_write]);
	}
	execve(cmd[0], cmd, envp);
	free(input_cmd);
	exit(3);
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
			//free_config
			exit(0);
		}
		else if (pid == 0)
			manager(config, cmds[i], i, config->pipes_nb + 1);
		++i;
	}
	close_all_pipes(config);
	waiting_all_sons(config->pipes_nb + 1);
}

int init_pipes(t_config *config)
{
	size_t i;
	
	i = 0;
	while (i < config->pipes_nb * 2)
	{
		if (pipe(config->pipes_fd + i) == -1)
		{
			close_all_pipes(config->pipes_fd, i + 2);
			return (0);
		}
		i += 2;
	}
	return (1);
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
	if (!init_pipes(&config))
	{
		clean_2d_tab(cmds);
		//free config
		return (0);
	}
	run_pipe(cmds, envp, pipes_fd, pipes_nb);
	clean_2d_tab(cmds);
	return (1);
}
