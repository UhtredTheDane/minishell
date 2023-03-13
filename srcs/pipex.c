#include "../includes/pipex.h"
#include "../includes/parsing.h"

char	**make_cmd(char *one_string_cmd, char **envp)
{
	char	**cmd;
	char	*tempo_cmd;
	size_t	i;

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

char **search_cmd(t_parse *p, t_cmd *cmd)
{
	char	**cmd;

	cmd = make_cmd(cmd->cmd[0], p->envp);
	if (!cmd)
	{
			close(config->pipes_fd[num_write]);
			close(config->pipes_fd[num_read]);
		free(input_cmd);
		free(config->pipes_fd);
		return (NULL);
	}
	return (cmd);
}

void manager(t_parse *p, t_cmd *cmd,int *pipe_in, int *pipe_out)
{
	cmd->cmd = search_cmd(p, cmd);
	free(input_cmd);
	if (!cmd)
		exit(1);

	dup2(pipe_in[], 0);
	if (!link_stdout(config, num_write))
		exit(3);
	
	execve(cmd[0], cmd, config->envp);
	free(config->pipes_fd);
	exit(4);
}

int init_pipe(int *pipe_in, int *pipe_out, int num_pipe, int pipes_nb)
{
	if(num_pipe > 0)
	{
		pipe_in = pipe_out;
	}
	if (num_pipe >= 0 && num_pipe < pipes_nb -1)
	{
		if (!pipe(pipe_out))
			return (0);
	}
	else
		pipe_out = NULL;
	return(1);
}

int	run_pipe(t_parse *p)
{
	int	i;
	pid_t pid;
	t_cmd *current;
	int *pipe_in;
	int *pipe_out;

	current = p->first;
	i = 0;
	while (current)
	{
		if (!init_pipe(pipe_in, pipe_out, i, p->count))
			return (0);
		pid = fork();
		if (pid < 0)
		{
			perror("Probleme fork");
			return(0);
		}
		else if (pid == 0)
			manager(p, current, pipe_in, pipe_out);
		if(i < p->count - 1)
			close(pipe_out[1])
		if(pipe_in)
			close(pipe_in[0]);
		current = current->next;
		++i;
	}
	waiting_all_sons(p->count);
}

int	execute(t_parse *p)
{
	if(!edit_parsing(p))
	{
		printf("parsing has been cancel for some reasons");
		return(0);
	}
	if(!split_cmd(p))
	{
		printf("split failed for some reason");
		return(0);
	}	
	if(!run_pipe(p))
		return(0);
	//	display_parse(p);
	free_parse(p);
	return (1);
}
