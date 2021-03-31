#include <stdio.h>
#include <stdlib.h>     // exit
#include <unistd.h>     // fork, close
#include <string.h>     // strdup
#include <fcntl.h>      // open(flags, modes)
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int ret_fork = fork();
    if (ret_fork < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (ret_fork == 0) {
        // child: redirect standard output to a file
        close(STDOUT_FILENO); 
        open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
        // now exec "wc"...
        char *myargs[3];
        myargs[0] = strdup("wc");   // program: "wc" (word count)
        myargs[1] = strdup("p4.c"); // argument: file to count
        myargs[2] = NULL;           // marks end of array
        execvp(myargs[0], myargs);  // runs word count
    } else {
        // parent goes down this path (original process)
        wait(NULL);
    }
    return 0;
}
