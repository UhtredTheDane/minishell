/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:35:02 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/18 02:09:42 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/heredoc.h"
#include "../../includes/error.h"

int	max(char *input, char *word)
{
	if (ft_strlen(input) > ft_strlen((word)))
		return (ft_strlen(input));
	return (ft_strlen(word));
}

char	*get_name(t_cmd *cmd, int i, int op)
{
	int	start_w;

	i = skip_space(cmd->s[0], i);
	if (!cmd->s[0][i])
		return (syntax_err(cmd->s[0] + i, cmd), NULL);
	if (is_special(cmd->s[0][i], "<> "))
		return (syntax_err(cmd->s[0] + i, cmd), NULL);
	start_w = i;
	while (cmd->s[0][i] && !is_special(cmd->s[0][i], "<> "))
	{
		if (cmd->s[0][i] == '\'')
			i = skip_to_x(cmd->s[0], i + 1, "\'");
		else if (cmd->s[0][i] == '\"')
			i = skip_to_x(cmd->s[0], i + 1, "\"");
		i++;
	}
	return (trimming(op, cmd, start_w, i));
}

int	run_heredoc(t_cmd *cmd, char *word, t_envp *envp)
{
	char	*input;

	close(cmd->pipe_heredoc[0]);
	if (!update_interactive_sigint())
		return (0);
	input = readline("Heredoc>");
	while (input && strncmp(input, word, max(input, word)))
	{
		input = replace_dollards_heredoc(input, envp);
		write(cmd->pipe_heredoc[1], input, ft_strlen(input) + 1);
		write(cmd->pipe_heredoc[1], " \n", 2);
		free(input);
		input = readline("Heredoc>");
	}	
	close(cmd->pipe_heredoc[1]);
	if (!input)
	{
		printf("Heredoc expect %s not end of file\n", word);
		return (0);
	}
	free(input);
	return (1);
}

int	get_heredoc(t_parse *p, t_cmd *cmd, char *word)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("Probleme fork");
		return (1);
	}
	else if (pid == 0)
		son_heredoc(p, cmd, word);
	free(word);
	close(cmd->pipe_heredoc[1]);
	pid = waitpid(-1, &status, 0);
	if (!WIFEXITED(status))
		return (1);
	return (0);
}

int	here_doc(t_parse *p, t_cmd *cmd, int i, int op)
{
	char	*delim;

	delim = get_name(cmd, i, op);
	if (!delim)
		return (2);
	delim = new_delim(p, delim);
	if (cmd->pipe_heredoc)
	{
		close(cmd->pipe_heredoc[0]);
		free(cmd->pipe_heredoc);
	}
	cmd->pipe_heredoc = malloc(sizeof(int) * 2);
	if (!cmd->pipe_heredoc)
		return (1);
	if (pipe(cmd->pipe_heredoc) == -1)
	{
		free(cmd->pipe_heredoc);
		return (1);
	}
	return (get_heredoc(p, cmd, delim));
}
