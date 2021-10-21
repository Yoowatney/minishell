#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[], char *envp[])
{
	int pid;
	int fd;

	int pipes1[2];
	int	pipes2[2];

	int status;
	char *args1[] = {"ls", NULL};
	char *args2[] = {"grep", "a", NULL};
	char *args3[] = {"grep", "t", NULL};

	pipe(pipes1);
	pipe(pipes2);

	pid = fork();
	if (pid == 0)
	{
		dup2(pipes1[1], 1);
		close(pipes1[0]);
		close(pipes1[1]);
		execve("/bin/ls", args1, envp);
	}
	else
	{
		close(pipes1[1]);
		waitpid(pid, &status, 0);
	}
	// ls | : pipes1에 씀

	pid = fork();
	if (pid == 0)
	{
		dup2(pipes1[0], 0); // STDIN을 pipes1로 리다이렉션
		close(pipes1[0]);

		dup2(pipes2[1], 1); // 결과값을 pipes2에 쓰겠다
		close(pipes2[1]);
		close(pipes2[0]);
		execve("/usr/bin/grep", args2, envp);
	}
	else
	{
		close(pipes1[0]); // pipes1[0] refcnt 0
		close(pipes2[1]); // pipes2[1] refcnt 0
		waitpid(pid, &status, 0);
	}
	//  ls | grep a |

	pid = fork(); // pipes2[0] refcnt 2
	if (pid == 0)
	{
		dup2(pipes2[0], 0);
		close(pipes2[0]);
		execve("/usr/bin/grep", args3, envp);
	}
	else
	{
		close(pipes2[0]);
		waitpid(pid, &status, 0);
	}
	// ls | grep a | grep t
	fd = open("./test.txt", O_CREAT | O_WRONLY, 0777);
	printf("fd : %d\n", fd);
	return (0);
}
