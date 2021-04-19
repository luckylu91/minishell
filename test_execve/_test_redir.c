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
	
	if (child == 0)
	{
		dup2(fd, STDOUT_FILENO);
		
		puts("merguez");
		execve("/bin/echo", t, environ);
	}

	printf("test hors fork");
	close(fd);
}
