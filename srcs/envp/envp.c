/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:24:39 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/27 16:12:21 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/envp.h"

void delete_dico(t_envp *envp)
{
	t_envp *elem;
	t_envp *tempo;

	elem = envp;
	while (elem)
	{
		tempo = elem;
		elem = elem->next;
		free(tempo->key);
		free(tempo->value);
		free(tempo);
	}
}
int update_shlvl(t_envp *shell_envp)
{
	char *lvl;  
	int tempo_lvl;

	lvl = get_value(shell_envp, "SHLVL");
	if (lvl == NULL)
	{
		lvl = malloc(sizeof(char) * 2);
		if (!lvl)
			return (0);
		ft_strlcpy(lvl, "1", 2);
		ft_envp_add(&shell_envp, ft_envp_new("SHLVL", lvl));
	}
	else
	{
		tempo_lvl = ft_atoi(lvl);
		++tempo_lvl;
		lvl = ft_itoa(tempo_lvl);
		if (!set_value(shell_envp, "SHLVL", lvl))
			return (0);
	}
	return (1);
}

int add_pwd(t_envp **shell_envp)
{
	char *pwd;
	char *old_pwd;

	pwd = builtin_pwd();
	if (!pwd)
		return (0);
	ft_envp_add(shell_envp, ft_envp_new("PWD", pwd));
	old_pwd = malloc(sizeof(char));
	if (!old_pwd)
		return (0);
	old_pwd[0] = '\0';
	ft_envp_add(shell_envp, ft_envp_new("OLDPWD", old_pwd));
	return (1);
}

int create_entries(char *str, char **key, char **value)
{
	size_t key_len;
	size_t value_len;

	key_len = egal_pos(str);
	value_len = ft_strlen(str + key_len + 1);
	*key = create_key(str, key_len);
	if (!*key)
		return (0);
	*value = create_value(str, key_len, value_len);
	if (!*value)
		return (0);
	return (1);
}

t_envp  *create_shell_envp(char **envp)
{
	t_envp *shell_envp;
	char *key;
	char *value;
	size_t  i;

	i = 0;
	shell_envp = NULL;
	if (!envp[i] && !add_pwd(&shell_envp))
		return (NULL);
	while (envp[i])
	{
		if (!create_entries(envp[i], &key, &value))
			return (NULL);//avoir
		ft_envp_add(&shell_envp, ft_envp_new(key, value));
		++i;
	}
	update_shlvl(shell_envp);
	return (shell_envp);
}

t_envp	*ft_envp_new(char *key, char *value)
{
	t_envp	*res;

	res = malloc(sizeof(t_envp));
	if (!res)
		return (NULL);
	res->key = key;
	res->value = value;
	res->next = NULL;
	return (res);
}

void	ft_envp_add(t_envp **envp, t_envp *new)
{
	t_envp	*elem;

	if (envp && new)
	{
		if (!*envp)
			*envp = new;
		else
		{
			elem = *envp;
			while (elem->next)
				elem = elem->next;
			elem->next = new;
		}
	}
}
