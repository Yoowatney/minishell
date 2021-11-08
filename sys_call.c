#include "minishell.h"

void	*ft_malloc(int size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
		error_check("");
	return (ret);
}
