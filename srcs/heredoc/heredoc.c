#include "../../includes/heredoc.h"

int max(char *input,char *word)
{
	if (ft_strlen(input) > ft_strlen((word)))
		return (ft_strlen(input));
	return (ft_strlen(word));
}

char *get_name(t_cmd *cmd, int i, int op)
{
	int start_w;
		
	i = skip_space(cmd->s[0], i);
	if(is_special(cmd->s[0][i],"<> "))
		return(NULL);
	start_w = i;
	while(cmd->s[0][i] && !is_special(cmd->s[0][i],"<> "))
	{
		if(cmd->s[0][i] == '\'')
			i = skip_to_X(cmd->s[0] + i, i + 1,"\'");
		else if(cmd->s[0][i] == '\"')
			i = skip_to_X(cmd->s[0] + i, i + 1,"\"");
		i++;
	}
	return(trimming(op,cmd, start_w, i));
}

int run_heredoc(t_cmd *cmd, char *word)
{
	char *value;
	char *input;
	int size;

	close(cmd->pipe_heredoc[0]);
	if (!update_sigint_interactive(1))
		return (0);
	input = readline("Heredoc>");
	value = "";
	while(input && strncmp(input, word, max(input, word)))
	{
		size = ft_strlen(input) + ft_strlen(value) + 2; 
		value = malloc(size);
		if(!value)
		{
			close(cmd->pipe_heredoc[1]);
			return(0);	
		}
		value[0] = '\0';
		ft_strlcat(value, input, size);
		ft_strlcat(value,"\n",size);
		write(cmd->pipe_heredoc[1], value, size);
		input = readline("Heredoc>");
	}
	if(!input)
	{
		printf("Heredoc expect %s not end of file\n", word);
		close(cmd->pipe_heredoc[1]);
		return(0);
	}
	close(cmd->pipe_heredoc[1]);
	return (1);
}
 
int get_heredoc(t_parse *p, t_cmd* cmd, char *word)
{
	pid_t pid;
	int status; 
	int return_code;

	p = (t_parse *) p;
	pid = fork();
	if (pid < 0)
	{
		perror("Probleme fork");
		return (0);
	}
	else if (pid == 0)
	{
		return_code = run_heredoc(cmd, word);
		exit(return_code);
	}
	if (!update_sigint_interactive(0))
		return (0);
	pid = waitpid(-1, &status, 0);
	if (!update_no_interactive_sigint()) 
		return (1);
	close(cmd->pipe_heredoc[1]);
	if (!WIFEXITED(status))
		return (0);
	return (1);	
}

int here_doc(t_parse *p, t_cmd *cmd, int i, int op)
{
	char *delim;

	delim = get_name(cmd,i,op);
	if(!delim)
		return(0);
	cmd->pipe_heredoc = malloc(sizeof(int) * 2);
	if (!cmd->pipe_heredoc)
			return (0);
	if (pipe(cmd->pipe_heredoc) == -1)
	{
		free(cmd->pipe_heredoc);
		return (0);
	}
	return (get_heredoc(p, cmd, delim));
}
