#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*void	sign(int sig)
 *{
 *    printf("got SIGINT\n");
 *    signal(SIGINT, SIG_DFL);
 *}
 *int main(int argc, char *argv[])
 *{
 *    signal(SIGINT, sign);
 *    while (1)
 *        pause();
 *    return (0);
 *}*/

int main(int argc, char *argv[], char *envp[])
{
	int pid;
	int pipes[2];
	int	status;

	char *args[] = {"grep", "a",  NULL};

	pipe(pipes);

	pid = fork();
	if (pid == 0)
	{
		dup2(pipes[0], 0);
		/*dup2(pipes[1], 1);*/
		close(pipes[0]);
		/*close(pipes[0]);*/
		close(pipes[1]);
		execve("/usr/bin/grep", args, envp);
		exit(0);
	}
	dprintf(pipes[1], "pear\n");
	close(pipes[0]);
	close(pipes[1]);
	/*int fd = open("./test.txt", O_CREAT | O_WRONLY, 0777);
	 *printf("fd : %d\n", fd);*/
	else
	{
		waitpid(pid, &status, 0);
		close(pipes[1]);
	}
	exit(0);

    int pipes2[2];

    pipe(pipes2);
	pid = fork();

	args[0] = "grep";
	args[1] = "a";
	args[2] = NULL;
	if (pid == 0)
	{
		dup2(pipes[0], 0);
		/*dup2(pipes2[1], 1);*/
		execve("/usr/bin/grep", args, envp);
		exit(0);
	}
	else
	{
		close(pipes[1]);
		waitpid(pid, &status, 0);
		close(pipes[0]);
	}
/*    return (0);
 *    exit(0);
 **/
	pid = fork();
	args[0] = "grep";
	args[1] = "t";
	args[2] = NULL;
	if (pid == 0)
	{
		dup2(pipes2[0], 0);
		close(pipes2[0]);
		execve("/usr/bin/grep", args, envp);
		exit(0);
	}
	else
	{
		close(pipes2[1]);
		waitpid(pid, &status, 0);
	}
	return (0);
}
