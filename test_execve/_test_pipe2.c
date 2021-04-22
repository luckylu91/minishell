// Example2.c
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main()
{
        int     filedes[2], nbytes;
        int		pipe2[2];
		pid_t   childpid;
        char    string[] = "Hello, world!\n";
        char    readbuffer[80];

        pipe(filedes);
        pipe(pipe2);
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                //close(filedes[0]);//Child process does not need this end of the pipe
				

                /* Send "string" through the output side of pipe */
                dup2(pipe2[1],filedes[1]);
				write(filedes[1], string, (strlen(string)+1));
                exit(0);
        }
        else
        {
                /* Parent proces closes up output side of pipe */
                //close(filedes[1]);//Parent process does not need this end of the pipe

                /* Read in a string from the pipe */
                nbytes = read(pipe2[0], readbuffer, sizeof(readbuffer));
                printf("Read string: %s", readbuffer);
        }
        
        return(0);
}
