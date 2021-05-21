#include <stdlib.h>
#include "libft.h"

char	**split_path(void)
{
	char	*str;
	char	**res;

	str = getenv("PATH");
	res = ft_split(str, ":");
	return (res);
}
