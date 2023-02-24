#include "../includes/pipex.h"

char	**make_cmd(char *one_string_cmd, char **envp)
{
	char	**cmd;
	char	*tempo_cmd;
	size_t	i;

	cmd = ft_split(one_string_cmd, ' ');
	if (!cmd)
		return (NULL);
	tempo_cmd = format_string(cmd);
	if (!tempo_cmd)
		return (NULL);
	cmd[0] = tempo_cmd;
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		++i;
	tempo_cmd = find_path(envp, cmd, i);
	if (!tempo_cmd)
		return (NULL);
	cmd[0] = tempo_cmd;
	return (cmd);
}

void	receiver(char *input_cmd, char **envp, int *pipe_fd, size_t num_proc, size_t pipes_nb)
{
	char	**cmd;


	//verif make cmd
	cmd = make_cmd(input_cmd, envp);
	
	pipes_nb = (size_t) pipes_nb;
	num_proc = (size_t) num_proc;
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
	execve(cmd[0], cmd, envp);
	exit(0);

}
void	sender(char *input_cmd, char **envp, int *pipe_fd, size_t num_proc, size_t pipes_nb)
{
	char	**cmd;
	//verif make cmd
	cmd = make_cmd(input_cmd, envp);
	pipes_nb = (size_t) pipes_nb;
	num_proc = (size_t) num_proc;

		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
	execve(cmd[0], cmd, envp);
	exit(0);

}

int	run_pipe(int *pipe_fd, char *in_put, char **envp)
{
	size_t	i;
	size_t	pipes_nb;
	pid_t	pid;
	char	**cmds;

	i = 0;
	pipes_nb = 0;
	while (*(in_put + i))
	{
		if (*(in_put + i) == '|')
			++pipes_nb;
		++i;
	}
	cmds = ft_split(in_put, '|');
	envp = (char **) envp;

	i = 0;
	while (i < pipes_nb + 1)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Probleme fork");
			return(0);
		}
		else if (pid == 0)
		{
			if (i == 0)
				sender(cmds[i], envp, pipe_fd, i, pipes_nb);
			else
				receiver(cmds[i], envp, pipe_fd, i, pipes_nb);
		}
		++i;
	}
	return (1);
}
