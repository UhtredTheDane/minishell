#include "../includes/pipex.h"


void    builtin_echo(const char *message, int n_option)
{
    printf("%s", message);
    if (!n_option)
        write(0, "\n", 1);
}

/*
void builtin_cd(const char *path)
{
    if (chdir(path) == -1)
        perror("Erreur cd\n");
}

void    builtin_pwd()
{
    char    buffer[4000];

    location = getcwd(buffer, 4000);
    if (!getcwd(buffer, 4000);)
    {
        perror("Erreur pwd\n");
        exit(0);
    }
    printf("%s\n", buffer);
}
*/

//void    builtin_export(t_dico *dico, const char *key, const char *value)
//{
    
//}
/*
void    builtin_unset()
{

}

*/

void    builtin_env(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        ++i;
    }
}

void    builtin_exit(int return_value)
{
    printf("exit");
    exit(return_value);
}