#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Hache # tag

int main()
{
	int		fd12[2];
	int		fd23[2];
	pid_t	lspid;
	pid_t	sortpid;
	pid_t	greppid;
	char	*cat_path = "/usr/bin/cat";
	char	*cat_argv[10] = {"cat", "main.c", NULL};
	char	*sort_path = "/usr/bin/sort";
	char	*sort_argv[10] = {"sort", NULL};
	char	*grep_path = "/usr/bin/grep";
	char	*grep_argv[10] = {"grep", "#", NULL};
	int		wstatus;

	setbuf(stdout, NULL);

	printf("lalala\n");
	pipe(fd12);
	lspid = fork();
	if (lspid != 0)
	{
		close(fd12[0]);
		dup2(fd12[1], STDOUT_FILENO);
		execve(cat_path, cat_argv, NULL);
	}
	close(fd12[1]);
	pipe(fd23);
	sortpid = fork();
	if (sortpid != 0)
	{
		close(fd23[0]);
		dup2(fd12[0], STDIN_FILENO);
		dup2(fd23[1], STDOUT_FILENO);
		execve(sort_path, sort_argv, NULL);
	}
	close(fd12[0]);
	//waitpid(lspid, &wstatus, 0);
	close(fd23[1]);
	greppid = fork();
	if (greppid != 0)
	{
		dup2(fd23[0], STDIN_FILENO);
		execve(grep_path, grep_argv, NULL);
	}
	close(fd23[0]);
	// waitpid(sortpid, &wstatus, 0);
	// waitpid(greppid, &wstatus, 0);
}
