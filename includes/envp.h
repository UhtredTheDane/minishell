/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:08:17 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/13 15:13:41 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "pipex.h"

typedef struct s_envp
{
	char			*value;
	char			*key;
	struct s_envp	*next;
}	t_envp;

int		set_value(t_envp *envp, char *key, char *value);
int		ft_envp_size(t_envp *envp);
int		update_shlvl(t_envp *shell_envp);
int		add_pwd(t_envp **shell_envp);
int		create_entries(char *str, char **key, char **value);
char	**create_envp_tab(t_envp *envp);
char	*get_value(t_envp *envp, char *key);
char	*create_key(char *str, size_t key_len);
char	*create_value(char *str, size_t key_len, size_t value_len);
void	delete_dico(t_envp *envp);
void	ft_envp_add(t_envp**lst, t_envp *new);
size_t	egal_pos(char *key);
size_t	choose_size(char *key, char *elem_key);
t_envp	*ft_envp_new(char *key, char *value);
t_envp	*create_shell_envp(char **envp);
#endif
