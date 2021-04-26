#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Hache # tag

int main()
{
	int		fd_ab[2];
	int		fd_bc[2];
	pid_t	lspid;
	pid_t	sortpid;
	pid_t	greppid;
	char	*cat_path = "/bin/cat";
	char	*cat_argv[10] = {"cat", "main.c", NULL};
	char	*sort_path = "/usr/bin/grep";
	char	*sort_argv[10] = {"grep", "#", NULL};
	char	*grep_path = "/usr/bin/grep";
	char	*grep_argv[10] = {"grep", "i", NULL};
	int		wstatus;

	setbuf(stdout, NULL);

	printf("lalala\n");
	pipe(fd_ab);
	pipe(fd_bc);
	lspid = fork();
	if (lspid == 0)
	{
		close(fd_ab[0]);
		close(fd_bc[0]);
		close(fd_bc[1]);
		dup2(fd_ab[1], STDOUT_FILENO);
		close(fd_ab[1]);
		execve(cat_path, cat_argv, NULL);
	}
	waitpid(lspid, &wstatus, 0);
	// printf("wstatus : %d\n", wstatus);
	sortpid = fork();
	if (sortpid == 0)
	{
		printf("sort begin\n");
		close(fd_ab[1]);
		close(fd_bc[0]);
		dup2(fd_ab[0], STDIN_FILENO);
		dup2(fd_bc[1], STDOUT_FILENO);
		close(fd_ab[0]);
		close(fd_bc[1]);
		execve(sort_path, sort_argv, NULL);
	}
	close(fd_ab[0]);
	close(fd_ab[1]);
	waitpid(sortpid, &wstatus, 0);
	// printf("wstatus : %d\n", wstatus);
	greppid = fork();
	if (greppid == 0)
	{
		close(fd_bc[1]);
		dup2(fd_bc[0], STDIN_FILENO);
		close(fd_bc[0]);
		execve(grep_path, grep_argv, NULL);
	}
	close(fd_bc[0]);
	close(fd_bc[1]);
	waitpid(greppid, &wstatus, 0);
	// printf("watatus : %d\n", wstatus);
	printf("THE END\n");
}
