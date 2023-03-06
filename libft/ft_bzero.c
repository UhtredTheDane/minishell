#include "libft.h"

/*
 * Description:
 *
 * Erases the data in the n bytes of the memory starting at the location 
 * pointed to by s, by writing zeros (bytes containing '\0') to that area.
 */

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s_char;
	size_t			i;

	s_char = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		*(s_char + i) = '\0';
		i++;
	}
}
