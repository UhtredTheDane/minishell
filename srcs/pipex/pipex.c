#include "../../includes/pipex.h"

char	*format_string(char *name_cmd)
{
	char	*temp;

	temp = ft_strjoin("/", name_cmd);
	if (!temp)
		return (NULL);
	free(name_cmd);
	return (temp);
}

char	*find_path(char **envp, char *cmd, size_t i)
{
	char	*temp;

	temp = get_path(envp[i] + 5, cmd);
	if (!temp)
	{
		return (NULL);
	}
	free(cmd);
	return (temp);
}

char	*make_cmd(t_parse *p, char *name_cmd)
{
	char	*cmd;
	char	*tempo_cmd;
	size_t	i;
	char **envp;

	envp = create_envp_tab(p->envp);
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

	cmd_name = make_cmd(p, cmd->cmd[0]);
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
		{
			manager(p, current, i);
			exit(4);
		}
		current = current->next;
		++i;
	}
	close_all_pipes(p);
	waiting_all_sons(p->count);
	return (1);
}