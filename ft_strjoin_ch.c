#include "minishell.h"

char	*ft_strjoin_ch(char *s1, char c)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = 0;
	if (!s1 || !c)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!ret)
		return (NULL);
	tmp = ret;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}	
	ret[i] = c;
	i++;
	ret[i] = 0;
	free(s1);
	s1 = NULL;
	return (tmp);
}

char	*ft_strjoin_not(char *s1, char *s2)
{
	char	*ret;

	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
		return (!(s1) ? s2 : s1);
	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
	{
		exit(errno);
		return (NULL);
	}
	ft_strjoin_sub(s1, s2, &ret);
	
	return (ret);
}
