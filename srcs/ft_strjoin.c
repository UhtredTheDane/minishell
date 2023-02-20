#include "../includes/main.h"

/*
 * Description:
 *
 * Allocates and returns a new string, which is the result of the concatenation 
 * of s1 and s2.
 */

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s_len;
	size_t	i;
	char	*s_join;

	if (!s1 || !s2)
		return (NULL);
	s_len = ft_strlen(s1) + ft_strlen(s2);
	s_join = malloc(sizeof(char) * (s_len + 1));
	if (!s_join)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		if (*s1)
			*(s_join + i) = *(s1++);
		else
			*(s_join + i) = *(s2++);
		i++;
	}
	*(s_join + i) = '\0';
	return (s_join);
}

