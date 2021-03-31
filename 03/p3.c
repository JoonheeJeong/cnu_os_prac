#include <stdio.h>
#include <stdlib.h>     // exit
#include <unistd.h>     // getpid, fork, execvp
#include <string.h>     // strdup
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int ret_fork = fork();
    if (ret_fork < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (ret_fork == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        char *myargs[3];
        myargs[0] = strdup("wc");   // program: "wc" (word count)
        myargs[1] = strdup("p3.c"); // argument: file to count
        myargs[2] = NULL;           // marks end of array
        execvp(myargs[0], myargs);  // runs word count
        printf("this shouldn't print out");
    } else {
        // parent goes down this path (original process)
        int ret_wait = wait(NULL);
        printf("hello, I am parent of %d (ret_wait:%d) (pid:%d)\n",
	       ret_fork, ret_wait, (int) getpid());
    }
    return 0;
}
