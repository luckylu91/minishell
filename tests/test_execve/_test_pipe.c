// Example2.c
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
int main()
{
        int     filedes[2], nbytes;
        pid_t   childpid;
        char    string[] = "Hello, world!\n";
		char    writebuffer[80];

		char    writebuffer2[80];
        char    readbuffer[80];

		setbuf(stdout, NULL);
        pipe(filedes);
        
          printf(" ici f1 = %i f2 = %i \n", filedes[0], filedes[1]);
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
				bzero(writebuffer, 32);

				bzero(writebuffer2, 32);
                //close(filedes[0]);//Child process does not need this end of the pipe

                /* Send "string" through the output side of pipe */
          printf(" ici 1 \n");
				read(STDIN_FILENO, writebuffer, sizeof(writebuffer));
			printf(" write = |%s| \n",writebuffer); 	
          printf(" ici 2\n");
				write(filedes[1], writebuffer, (strlen(writebuffer)+1));

				bzero(writebuffer, 32);
          printf(" ici 3\n");
			printf(" read = %li \n",read(STDIN_FILENO, writebuffer2, sizeof(writebuffer2)));
			printf("error = %s\n",strerror(errno));	
			printf(" write 2= |%s| \n",writebuffer2); 	
          printf(" ici 4\n");
				write(filedes[1], writebuffer2, (strlen(writebuffer2)+1));

                exit(0);
        }
        else
        {
                /* Parent proces closes up output side of pipe */
          printf(" ici 6\n");
                //close(filedes[1]);//Parent process does not need this end of the pipe
	
          printf(" ici 5\n");
                /* Read in a string from the pipe */
                nbytes = read(filedes[0], readbuffer, sizeof(readbuffer));
                printf("Read string: %s", readbuffer);
			nbytes = read(filedes[0], readbuffer, sizeof(readbuffer));
                printf("Read string: %s", readbuffer);

        }
        
        return(0);
}
