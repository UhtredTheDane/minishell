#include "../../includes/execute.h"

int manager(t_parse *p, t_cmd *cmd, int num_proc)
{
	int num_write;
	int num_read;

	int flags;

	int old_stdin;
	int old_stdout;

	set_num_pipe(p, &num_read, &num_write, num_proc);
	close_useless_pipes(p, num_read, num_write);
	old_stdin = dup(0);
	old_stdout = dup(1);
	if (cmd->filename_in)
	{
		cmd->in = open(cmd->filename_in, O_RDONLY);
		dup2(cmd->in, 0);
		close(cmd->in);
	}
	else
		if (!link_stdin(p, num_read))
			return(2);
	if (cmd->filename_out)
	{
		flags = O_WRONLY | O_CREAT;
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
			return(3);
	if (execute_builtin(p, cmd))
	{
		dup2(old_stdin, 0);
		dup2(old_stdout, 1);
		return(0);
	}
	else
	{
		cmd->cmd[0] = search_cmd(p, cmd, num_read, num_write);
		if (!cmd->cmd[0])
			return(1);
		execve(cmd->cmd[0], cmd->cmd, create_envp_tab(p->envp));//attetion bien free
	}
	return(4);
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
	free_parse(p);
	return (1);
}
