#include "../includes/pipex.h"

size_t  egal_pos(char *key)
{
    size_t i;

    i = 0;
    while (key[i])
    {
        if (key[i] == '=')
            return (i);
        ++i;
    }
    return (0);
}

char **create_envp_tab(t_dico *dico)
{
    char **envp;
    int nb_env;
    int i;
    char *temp;
    nb_env = ft_dicosize(dico);
    envp = malloc(sizeof(char *) * (nb_env + 1));
    if (!envp)
        return (NULL);
    envp[nb_env] = NULL;
    i = 0;
    while (dico)
    {
        temp = ft_strjoin(dico->key, "=");
        envp[i] = ft_strjoin(temp, dico->value);
        free(temp);
        dico = dico->next;
        ++i;
    }
    return (envp);
}

t_dico  *create_dico(char **envp)
{
    size_t  i;
    char *key;
    char *value;
    t_dico *dico;
    size_t keylen;
    size_t valuelen;

    i = 0;
    dico = NULL;
    while (envp[i])
    {
        keylen = egal_pos(envp[i]);
        key = malloc(sizeof(char) * (keylen + 1));
        if (!key)
            return (NULL);
        ft_strlcpy(key, envp[i], keylen + 1);
        valuelen = ft_strlen(envp[i] + keylen + 1);
        value = malloc(sizeof(char) * (valuelen + 1));
        if (!value)
            return (NULL);
        ft_strlcpy(value, envp[i] + keylen + 1, valuelen + 1);
        ft_dicoadd(&dico, ft_diconew(key, value));
        ++i;
    }
    return (dico);
}

int	ft_dicosize(t_dico *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

t_dico	*ft_diconew(char *key, char *value)
{
	t_dico	*res;

	res = malloc(sizeof(t_dico));
	if (!res)
		return (NULL);
    res->key = key;
	res->value = value;
	res->next = NULL;
	return (res);
}


int   set_value(t_dico *envp, char *key, char *value)
{
    size_t size_key;

    while (envp)
    {
        size_key = ft_strlen(envp->key);
        if (ft_strncmp(envp->key, key, size_key) == 0)
        {
            free(envp->value);
            envp->value = value;
            return (1);
        }
        envp = envp->next;
    }
    return (0);
}

char    *getvalue(t_dico *envp, char *key)
{

    size_t size_key;

    while (envp)
    {
        size_key = ft_strlen(envp->key);
        if (ft_strncmp(envp->key, key, size_key) == 0)
            return (envp->value);
        envp = envp->next;
    }
    return (NULL);
}

void	ft_dicoadd(t_dico **lst, t_dico *new)
{
	t_dico	*elem;

	if (lst && new)
	{
		if (!*lst)
			*lst = new;
		else
		{
			elem = *lst;
			while (elem->next)
				elem = elem->next;
			elem->next = new;
		}
	}
}

void delete_key(t_dico **envp, char *key)
{
    size_t size_key;
    t_dico *prev;
    t_dico *elem;

    if (envp)
    {
        elem = *envp;
        while (elem)
        {
            size_key = ft_strlen(elem->key);
            if (ft_strncmp(elem->key, key, size_key) == 0)
            {
               free(elem->key);
               free(elem->value);
               if (elem == *envp)
                    *envp = elem->next;
                else
                    prev->next = elem->next;
                free(elem);
                break;
            }
            prev = elem;
            elem = elem->next;
        }
    }
}
