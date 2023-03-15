#include "../includes/pipex.h"
#include "../includes/parsing.h"

char	*make_cmd(char *name_cmd, char **envp)
{
	char	*cmd;
	char	*tempo_cmd;
	size_t	i;

	cmd = format_string(name_cmd);
	if (!cmd)
		return (NULL);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		++i;
	tempo_cmd = find_path(envp, cmd, i);
	if (!tempo_cmd)
		return (NULL);
	return (tempo_cmd);
}

char *search_cmd(t_parse *p, t_cmd *cmd, int num_read, int num_write)
{
	char	*cmd_name;

	cmd_name = make_cmd(cmd->cmd[0], p->envp);
	if (!cmd_name)
	{
		if (num_write)
			close(p->pipes_fd[num_write]);
		if (num_read)
			close(p->pipes_fd[num_read]);
		free(p->pipes_fd);
		return (NULL);
	}
	return (cmd_name);
}

void manager(t_parse *p, t_cmd *cmd, int num_proc)
{
	int num_write;
	int num_read;
	int flags;
	
	set_num_pipe(p, &num_read, &num_write, num_proc);
	close_useless_pipes(p, num_read, num_write);
	cmd->cmd[0] = search_cmd(p, cmd, num_read, num_write);
	if (!cmd->cmd[0])
		exit(1);
	if (cmd->filename_in)
	{
		cmd->in = open(cmd->filename_in, O_RDONLY);
		dup2(cmd->in, 0);
		close(cmd->in);
	}
	else
		if (!link_stdin(p, num_read))
			exit(2);
	
	if (cmd->out)
	{
		flags = O_WRONLY | O_CREAT;
		if (cmd->append)
		{
			printf("couco\n");
			flags = flags | O_TRUNC;
		}
		cmd->out = open(cmd->filename_out, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		dup2(cmd->out, 1);
		close(cmd->out);
	}
	else
		if (!link_stdout(p, num_write))
			exit(3);
	execve(cmd->cmd[0], cmd->cmd, p->envp);
	exit(4);
}

int	run_pipe(t_parse *p)
{
	int	i;
	pid_t pid;
	t_cmd *current;

	current = p->first;
	i = 0;
	while (current)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Probleme fork");
			return(0);
		}
		else if (pid == 0)
			manager(p, current, i);
		current = current->next;
		++i;
	}
	close_all_pipes(p);
	waiting_all_sons(p->count);
	return (1);
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
	{
		printf("Impossible de lancer les pip\n");
		return(0);
	}
	free_parse(p);
	return (1);
}
