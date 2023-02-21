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
/*
void	receiver(char **argv, char **envp, int *pipe_fd)
{
	int		fd_stdout;
	char	**cmd;

	close(pipe_fd[1]);
	cmd = NULL;
	fd_stdout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR
			| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd_stdout == -1)
		clean_exit(cmd, pipe_fd[0], fd_stdout, 2);
	cmd = make_cmd(argv[3], envp);
	if (!cmd)
		clean_exit(cmd, pipe_fd[0], fd_stdout, 5);
	if (dup2(pipe_fd[0], 0) == -1)
		clean_exit(cmd, pipe_fd[0], fd_stdout, 3);
	if (dup2(fd_stdout, 1) == -1)
		clean_exit(cmd, pipe_fd[0], fd_stdout, 3);
	close(pipe_fd[0]);
	if (execve(cmd[0], cmd, envp) == -1)
		clean_exit(cmd, -1, fd_stdout, 4);
}

void	sender(char **argv, char **envp, int *pipe_fd)
{
	int		fd_stdin;
	char	**cmd;

	close(pipe_fd[0]);
	cmd = NULL;
	fd_stdin = open(argv[1], O_RDONLY);
	if (fd_stdin == -1)
		clean_exit(cmd, pipe_fd[1], fd_stdin, 2);
	cmd = make_cmd(argv[2], envp);
	if (!cmd)
		clean_exit(cmd, pipe_fd[1], fd_stdin, 5);
	if (dup2(fd_stdin, 0) == -1)
		clean_exit(cmd, pipe_fd[1], fd_stdin, 3);
	if (dup2(pipe_fd[1], 1) == -1)
		clean_exit(cmd, pipe_fd[1], fd_stdin, 3);
	close(pipe_fd[1]);
	if (execve(cmd[0], cmd, envp) == -1)
		clean_exit(cmd, -1, fd_stdin, 4);
}
*/

void	receiver(char *input_cmd, char **envp, int *pipe_fd, size_t num_proc, size_t pipes_nb)
{
	char	**cmd;
	int		fd_stdout;

	fd_stdout = open("test", O_WRONLY | O_CREAT, S_IRUSR
			| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	//verif make cmd
	cmd = make_cmd(input_cmd, envp);
	pipes_nb = (size_t) pipes_nb;
	num_proc = (size_t) num_proc;
	
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		dup2(fd_stdout, 1);
		close(pipe_fd[0]);
	execve(cmd[0], cmd, envp);
	//verif execve
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
	//verif execve
}

int	run_pipe(char *in_put, char **envp)
{
	size_t	i;
	size_t	pipes_nb;
	pid_t	pid;
	char	**cmds;
	int	pipes_fd[2];

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

	if (pipe(pipes_fd))
	{
		printf("Erreur init pipe\n");
		return (0);
	}

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
				sender(cmds[i], envp, pipes_fd, i, pipes_nb);
			else
				receiver(cmds[i], envp, pipes_fd, i, pipes_nb);
		}
		++i;
	}
	return (1);
}
