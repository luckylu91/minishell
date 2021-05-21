#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
 extern char **environ;
int main(int ag, char *av[])
{
	char *t[5];
	t[0] = "ls";
	
	t[1] = "-a";
	t[2] = "./..";	
	t[3] = NULL;
	//int f;
	//f = fork();
	//printf("f = %i\n", f);
	//if(f != 0)
	execve("/bin/ls",t,environ);
	printf(" apres execve\n");
}
