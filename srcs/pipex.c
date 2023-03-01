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

void	receiver(char *input_cmd, char **envp, int *pipe_fd)
{
	char	**cmd;

	cmd = make_cmd(input_cmd, envp);
	if (!cmd)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		free(input_cmd);
		exit(1);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], 0) == -1)
	{
		close(pipe_fd[0]);
		free(input_cmd);
		exit(2);
	}
	close(pipe_fd[0]);
	execve(cmd[0], cmd, envp);
	free(input_cmd);
	exit(3);

}

void sender(char *input_cmd, char **envp, int *pipe_fd)
{
	char	**cmd;

	cmd = make_cmd(input_cmd, envp);
	if (!cmd)
	{
		
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		free(input_cmd);
		exit(1);
	}
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], 1) == -1)
	{
		close(pipe_fd[1]);
		free(input_cmd);
		exit(2);
	}
	close(pipe_fd[1]);
	execve(cmd[0], cmd, envp);
	free(input_cmd);
	exit(3);
}
/*
void manager(char *input_cmd, char **envp, int *pipe_fd)
{
	char	**cmd;

	cmd = make_cmd(input_cmd, envp);
	if (!cmd)
	{
		
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		free(input_cmd);
		exit(1);
	}
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], 1) == -1)
	{
		close(pipe_fd[1]);
		free(input_cmd);
		exit(2);
	}
	close(pipe_fd[1]);
	execve(cmd[0], cmd, envp);
	free(input_cmd);
	exit(3);
}
*/
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

void	run_pipe(char **cmds, char **envp, int *pipe_fd, size_t pipes_nb)
{
	size_t	i;
	pid_t	pid[2];

	i = 0;
	while (i < pipes_nb + 1)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			perror("Probleme fork");
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			exit(0);
		}
		else if (pid[i] == 0)
		{
			if (i == 0)
				sender(cmds[i], envp, pipe_fd);
			else
				receiver(cmds[i], envp, pipe_fd);
		}
		++i;
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}

int	init_pipe(int *pipe_fd, char *in_put, char **envp)
{
	size_t	pipes_nb;
	char	**cmds;

	pipes_nb = count_pipes(in_put);
	cmds = ft_split(in_put, '|');
	if (!cmds)
	{
		printf("Erreur ft_split |\n");
		return (0);
	}
	run_pipe(cmds, envp, pipe_fd, pipes_nb);
	clean_2d_tab(cmds);
	return (1);
}
