#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[])
{
	char *str;

	str = strerror(13);
	printf("%s\n", str);
}

	/*dup2(pipes[0], 0);
	 *close(pipes[1]);
	 *execve("usr/bin/grep", args, envp);*/
