#include "../../includes/execute.h"

extern int cmd_return;

int redirect_stdin(t_parse *p, t_cmd *cmd, int num_read)
{ 

	if (cmd->heredoc)
	{
		dup2(cmd->pipe_heredoc[0], 0);
		close(cmd->pipe_heredoc[0]);
	}
	else if (cmd->filename_in)
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
		flags = O_WRONLY | O_CREAT;
		if (cmd->append)
			flags = flags | O_APPEND;
		else
			flags = flags | O_TRUNC;
		cmd->out = open(cmd->filename_out, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		dup2(cmd->out, 1);
		close(cmd->out);
	}
	else
		if (!link_stdout(p, num_write))
			return(0);
	return (1);
}

int char_in_str(char c, char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		++i;
	}
	return (0);
}

/*
char *trim_double_quote(char *basic_str, char *charset)
{
	char	*tempo_str;
	char	*new_str;
	int	quote_pos;

	new_str = ft_strtrim(basic_str, char);
	if (!new_str)
			return (basic_str);
	free(basic_str);
	while (char_in_str('"', new_str))
	{
		quote_pos = skip_to_X(new_str, 0, "\"");
		new_str[quote_pos] = '\0';
		tempo_str = ft_strjoin(new_str, new_str + quote_pos + 1);
		free(new_str);
		new_str = tempo_str;
	}
	return (new_str);
}*/

char **update_for_grep(char **cmd)
{
	char **new_cmd;
	int i;
	int j;

	i = 0;
	while (cmd[i])
		i++;
	new_cmd = malloc(sizeof(char*) * (i + 2));
	if (!new_cmd)
		return (cmd);

	i = 0;
	j = 0;
	while(cmd[i])
	{
		if (j == 1)
			new_cmd[j] = ft_strdup("-a");
			//tester pour free
		else
		{
			new_cmd[j] = ft_strdup(cmd[i]);
			//tester poour free en cas d erreur
			++i;
		}
		++j;
	}
	new_cmd[j] = NULL;
	//free(cmd);
	return (new_cmd);
	
	
}

void prepare_cmd(t_cmd *cmd)
{
	size_t	i;
	int quote_pos;
	int double_pos;
	char *first;
	int current_pos;
	char *tempo_str;

	if (cmd->heredoc)
	{
		if (ft_strncmp(cmd->cmd[0], "grep", 4) == 0)
			cmd->cmd = update_for_grep(cmd->cmd);
	}
	i = 0;
	while (cmd->cmd[i])
	{
		current_pos = 0;
		while(cmd->cmd[i][current_pos])
		{
			quote_pos = skip_to_X(cmd->cmd[i], current_pos, "'");
			double_pos = skip_to_X(cmd->cmd[i], current_pos, "\"");
			if (quote_pos <= double_pos)
			{
				current_pos = quote_pos;
				first =  "'";
			}
			else
			{
				current_pos = double_pos;
				first = "\"";
			}
			if ((size_t) current_pos != ft_strlen(cmd->cmd[i]))
			{
				cmd->cmd[i][current_pos] = '\0';
				tempo_str = ft_strjoin(cmd->cmd[i], cmd->cmd[i] + current_pos + 1);
				free(cmd->cmd[i]);
				cmd->cmd[i] = tempo_str;

				current_pos = skip_to_X(cmd->cmd[i], current_pos, first);
				cmd->cmd[i][current_pos] = '\0';
				tempo_str = ft_strjoin(cmd->cmd[i], cmd->cmd[i] + current_pos + 1);
				free(cmd->cmd[i]);
				cmd->cmd[i] = tempo_str;
			}
		}
		++i;
	}
}




int execute_cmd(t_parse *p, t_cmd *cmd, int old_stdin, int old_stdout)
{
	int exec_return;

	prepare_cmd(cmd);
	if (is_builtin(cmd))
	{
		exec_return = execute_builtin(p, cmd);
		dup2(old_stdin, 0);
		dup2(old_stdout, 1);
		if (cmd->heredoc)
			unlink("heredoc");
		return (exec_return);
	}
	else
	{
		if (access(cmd->cmd[0], F_OK) == -1)
		{
			cmd->cmd[0] = search_cmd(p, cmd);
			if (!cmd->cmd[0])
			{
				//free
				printf("%s: command not found\n",cmd->s[0]);
				return (127);
			}
		}
		execve(cmd->cmd[0], cmd->cmd, create_envp_tab(p->envp));//attetion bien free
	}
	return (127);
}

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
	//display_parse(p);	
	if(!split_cmd(p))
	{
		printf("split failed for some reason");
		return(0);
	}
	//display_parse(p);	
	if (!p->pipes_fd && is_builtin(p->first))
		cmd_return = manager(p, p->first, 0);
	else if(!run_pipe(p))
	{
		printf("Impossible de lancer les pip\n");
		return(0);
	}
	return (1);
}
