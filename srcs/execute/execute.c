#include "../../includes/execute.h"

int redirect_stdin(t_parse *p, t_cmd *cmd, int num_read)
{ 
	if (cmd->filename_in)
	{
		cmd->in = open(cmd->filename_in, O_RDONLY);
		dup2(cmd->in, 0);
		close(cmd->in);
	}
	else
		if (!link_stdin(p, num_read))
			return(0);
	return (1);
}

int redirect_stdout(t_parse *p, t_cmd *cmd, int num_write)
{
	int flags;

	if (cmd->filename_out)
	{
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		if (cmd->append)
		{
		
			flags = flags | O_APPEND;
		}
		cmd->out = open(cmd->filename_out, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		dup2(cmd->out, 1);
		close(cmd->out);
	}
	else
		if (!link_stdout(p, num_write))
			return(0);
	return (1);
}

int execute_cmd(t_parse *p, t_cmd *cmd, int old_stdin, int old_stdout)
{
	if (execute_builtin(p, cmd))
	{
		dup2(old_stdin, 0);
		dup2(old_stdout, 1);
		return(1);
	}
	else
	{
		if (access(cmd->cmd[0], F_OK) == -1)
		{
			cmd->cmd[0] = search_cmd(p, cmd);
			if (!cmd->cmd[0])
			{
				//free
				return(0);
			}
		}
		execve(cmd->cmd[0], cmd->cmd, create_envp_tab(p->envp));//attetion bien free
	}
	return (0);
}

int manager(t_parse *p, t_cmd *cmd, int num_proc)
{
	int num_write;
	int num_read;
	int old_stdin;
	int old_stdout;

	set_num_pipe(p, &num_read, &num_write, num_proc);
	close_useless_pipes(p, num_read, num_write);
	old_stdin = dup(0);
	old_stdout = dup(1);
	if (!redirect_stdin(p, cmd, num_read))
		return (2);
	if (!redirect_stdout(p, cmd, num_write))
		return (3);
	if (!execute_cmd(p, cmd, old_stdin, old_stdout))
		return (4);
	/*if (num_write)
			close(p->pipes_fd[num_write]);
		if (num_read)
			close(p->pipes_fd[num_read]);
		free(p->pipes_fd);*/
	return (0);
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
	if (!p->pipes_fd && is_builtin(p->first))
		manager(p, p->first, 0);
	else if(!run_pipe(p))
	{
		printf("Impossible de lancer les pip\n");
		return(0);
	}
	display_parse(p);	
	free_parse(p);
	return (1);
}
