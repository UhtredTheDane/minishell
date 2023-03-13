#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*emplacement;
	size_t	i;
	size_t	max;

	max = SIZE_MAX;
	if (size && max / size < nmemb)
		return (NULL);
	emplacement = malloc(nmemb * size);
	if (!emplacement)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		*(emplacement + i) = '\0';
		i++;
	}
	if (size * nmemb == 0)
		emplacement[0] = '\0';
	return ((void *) emplacement);
}