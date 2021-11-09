#include "minishell.h"

void	close_L_fd(int fd, int copy[])
{
	if (fd != 0)
	{
		close(fd);
		if (dup2(copy[0], STDIN_FILENO) == -1)
			error_check("");
	}
}

void	close_R_fd(int fd, int copy[])
{
	if (fd != 0)
	{
		close(fd);
		if (dup2(copy[1], STDOUT_FILENO) == -1)
			error_check("");
	}
}
