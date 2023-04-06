#include "../../includes/execute.h"

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

char *remove_first(char *cmd, int *current_pos, int quote_pos, int double_pos)
{
    char *first;
    char *tempo_str;

    if (quote_pos <= double_pos)
	{
		*current_pos = quote_pos;
		first =  "'";
	}
	else
	{
		*current_pos = double_pos;
		first = "\"";
	}
    if ((size_t) *current_pos != ft_strlen(cmd))
	{
		cmd[*current_pos] = '\0';
		tempo_str = ft_strjoin(cmd, cmd + *current_pos + 1);
		free(cmd);
		cmd = tempo_str;
        *current_pos = skip_to_X(cmd, *current_pos, first);
		cmd[*current_pos] = '\0';
		tempo_str = ft_strjoin(cmd, cmd + *current_pos + 1);
		free(cmd);
		cmd = tempo_str;
	}
    return (cmd);
}

char *trim_quotes(char *cmd)
{
    int current_pos;
    int quote_pos;
	int double_pos;
	char *res;

    current_pos = 0;
    res = cmd;
	while(cmd[current_pos])
	{
		quote_pos = skip_to_X(res, current_pos, "'");
		double_pos = skip_to_X(res, current_pos, "\"");
		res = remove_first(res, &current_pos, quote_pos, double_pos);
	}
}

void prepare_cmd(t_cmd *cmd)
{
	size_t	i;

	if (cmd->heredoc)
	{
		if (ft_strncmp(cmd->cmd[0], "grep", 4) == 0)
			cmd->cmd = update_for_grep(cmd->cmd);
	}
	i = 0;
	while (cmd->cmd[i])
	{
		cmd->cmd[i] = trim_quotes(cmd->cmd[i]);
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