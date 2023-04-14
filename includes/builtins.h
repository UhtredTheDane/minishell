/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:02:15 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/14 23:38:47 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define PATH_MAX 4000
# include "pipex.h"
# include "envp.h"
# include "parsing.h"

typedef struct s_cmd	t_cmd;
typedef struct s_parse	t_parse;
typedef struct s_envp	t_envp;

int		is_env(t_cmd *cmd);
int		builtin_env(t_envp *envp, t_cmd *cmd);
int		is_exit(t_cmd *cmd);
int		builtin_exit(t_envp *envp, t_cmd *cmd);
int		is_all_digit(char *str);
int		is_entrie_valid(char *str, int egal_pos);
int		add_var(t_envp *envp, char *cmd, int egal_pos);
int		add_new_entries(t_envp *envp, char *key, char *value);
int		is_export(t_cmd *cmd);
int		builtin_export(t_envp *envp, t_cmd *cmd);
int		is_echo(t_cmd *cmd);
int		builtin_echo(t_cmd *cmd);
int		check_option(char *cmd_1);
int		is_unset(t_cmd *cmd);
int		builtin_unset(t_parse *p, t_cmd *cmd);
int		is_pwd(t_cmd *cmd);
int		is_cd(t_cmd *cmd);
int		builtin_cd(t_envp *envp, t_cmd *cmd);
int		update_env(t_envp *envp);
int		size_cmd(t_cmd *cmd);
int		env_with_pwd(t_envp *envp, char *pwd, char **new_pwd, char **old_pwd);
int		check_path(const char *path);
int		is_builtin(t_cmd *cmd);
int		execute_builtin(t_parse *p, t_cmd *cmd);
void	print_pwd(void);
void	delete_key(t_envp **envp, char *key);
void	show_env(t_envp *envp);
char	*new_key(char *cmd);
char	*new_value(char *cmd, int egal_pos);
char	*builtin_pwd(void);
char	*env_with_no_pwd(void);
char	*replace_home(t_cmd *cmd, char *home);
char	*init_path(t_envp *envp, t_cmd *cmd);
#endif
