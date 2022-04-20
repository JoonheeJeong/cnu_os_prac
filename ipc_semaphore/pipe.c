#include <stdio.h> // perror
#include <stdlib.h> // exit
#include <string.h> // strlen
#include <unistd.h> // pid_t, fork, write, read

#define BUF_SIZE 64

int main(void)
{
    int	    fd[2], nbytes;
    pid_t   childpid;
    char    msg[] = "Hello, world!\n";
    char    readbuf[BUF_SIZE];

    pipe(fd); // Create a pipe

    if((childpid = fork()) == -1) {
	perror("fork"); // Print a error message.
	exit(1);
    }

    if(childpid == 0) {
	close(fd[0]); // Child process closes read-end of pipe
	write(fd[1], msg, (strlen(msg)+1)); // Send "msg" through write-end of pipe
	exit(0);
    } else {
	close(fd[1]); // Parent process closes write-end of pipe
	nbytes = read(fd[0], readbuf, sizeof(readbuf)); // Read in a msg from the pipe
	printf("Received msg: %s", readbuf);
	printf("Received bytes: %d\n", nbytes);
    }

    return 0;
}
