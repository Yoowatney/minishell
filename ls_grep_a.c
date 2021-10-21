#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[], char *envp[])
{
	int pid;

	int pipes1[2];

	int status;
	char *args1[] = {"ls", NULL};
	char *args2[] = {"grep", "a", NULL};

	pipe(pipes1);

	pid = fork();
	if (pid == 0)
	{
		dup2(pipes1[1], 1);
		status = close(pipes1[0]);
		if (status == -1)
			printf("error\n");
		status = close(pipes1[1]);
		if (status == -1)
			printf("error\n");
		execve("/bin/ls", args1, envp); exit(0);
	}
	else
	{
		status = close(pipes1[1]);
		if (status == -1)
			printf("error\n");
		waitpid(pid, &status, 0);
	}

	pid = fork();
	if (pid == 0)
	{
		dup2(pipes1[0], 0);
		status = close(pipes1[0]);
		if (status == -1)
			printf("error\n");
		execve("/usr/bin/grep", args2, envp); exit(0);
	}
	else
	{
		status = close(pipes1[0]);
		if (status == -1)
			printf("error\n");
		waitpid(pid, &status, 0);
	}
	int fd = open("./test.txt", O_CREAT | O_WRONLY, 0777);
	printf("%d\n", fd);

	return (0);
}
