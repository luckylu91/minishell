#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
extern char **environ;
int main()
{

	char *t[5];
	t[0] = "echo";
	t[1] = "patate et mort";
	t[2] = NULL;
	int fd = open("redi", O_APPEND | O_CREAT | O_RDWR, 0666);
	printf("fd = %i \n", fd);
	pid_t child = fork();
	int 	fildes[2];
	pipe(fildes);
	if (child == 0)
	{
		dup2(fildes[1], STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
		execve("/bin/echo", t, environ);
	}

	printf("test hors fork");
	close(fd);
}
