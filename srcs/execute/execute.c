#include "../../includes/execute.h"

extern int cmd_return;

int manager(t_parse *p, t_cmd *cmd, int num_proc)
{
	int num_write;
	int num_read;
	int old_stdin;
	int old_stdout;
 
	if (p->pipes_fd)
		if (!update_sigint_interactive(1))
			return (0);
	set_num_pipe(p, &num_read, &num_write, num_proc);
	close_useless_pipes(p, num_read, num_write);
	old_stdin = dup(0);
	old_stdout = dup(1);
	if (!redirect_stdin(p, cmd, num_read))
		return (2);
	if (!redirect_stdout(p, cmd, num_write))
		return (3);
	return (execute_cmd(p, cmd, old_stdin, old_stdout));
	//free(p->pipes_fd); tout free
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
		cmd_return = manager(p, p->first, 0);
	else if(!run_pipe(p))
	{
		printf("Impossible de lancer les pipes\n");
		return(0);
	}
	return (1);
}
