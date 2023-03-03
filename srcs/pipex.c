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

void close_all_pipes(int *pipes_fd, int nb_pipes)
{
	int i;

	i = 0;
	while (i < nb_pipes * 2)
	{
		close(pipes_fd[i]);
		++i;
	}
}

void manager(char *input_cmd, char **envp, int *pipes_fd, int num_proc, int nb_procs)
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

void	run_pipe(char **cmds, char **envp, int *pipes_fd, size_t pipes_nb)
{
	size_t	i;
	pid_t pid;
	i = 0;
	while (i < pipes_nb + 1)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Probleme fork");
			close_all_pipes(pipes_fd, pipes_nb);
			exit(0);
		}
		else if (pid == 0)
			manager(cmds[i], envp, pipes_fd, i, pipes_nb + 1);
		++i;
	}
	close_all_pipes(pipes_fd, pipes_nb);
	waiting_all_sons(pipes_nb + 1);
}

int	init_pipe(char *in_put, char **envp)
{
	size_t	pipes_nb;
	char	**cmds;
	int *pipes_fd;
	size_t	i;

	pipes_nb = count_pipes(in_put);
	pipes_fd = malloc(sizeof(int) * pipes_nb * 2);
	if (!pipes_fd)
		return (0);
	cmds = ft_split(in_put, '|');
	if (!cmds)
	{
		printf("Erreur ft_split |\n");
		free(pipes_fd);
		return (0);
	}
	i = 0;
	while (i < pipes_nb * 2)
	{
		if (pipe(pipes_fd + i) == -1)
		{
			clean_2d_tab(cmds);
			close_all_pipes(pipes_fd, i + 2);
			free(pipes_fd);
			return (0);
		}
		i += 2;
	}
	run_pipe(cmds, envp, pipes_fd, pipes_nb);
	clean_2d_tab(cmds);
	return (1);
}
