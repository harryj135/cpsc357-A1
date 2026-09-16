#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int fibonacci(int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
        
    return fibonacci(n-1) + fibonacci(n-2);
}

int main(int argc, char* argv[]) {
    pid_t fr;
    int fibonacci_n;
    int fib_result;

    // pipe
    int    pipes[argc][2];
    char   buf[128];

    if (argc < 2) exit(0);

    for (int i = 1; i < argc; i++) {
        pipe(pipes[i]);
        fr = fork();
        if (fr < 0) {
            printf("error!\n");
            exit(-1);
        } else if (fr == 0) {  
            // close read file descriptor
            close(pipes[i][0]);

            fibonacci_n = atoi(argv[i]);

            // use sprintf to print string to buf
            sprintf(buf, "Child Process (PID %d) F_{%d} = %d\n", getpid(), fibonacci_n, fibonacci(fibonacci_n));
            // write buf to pipe write file descriptor
            write(pipes[i][1], &buf, strlen(buf));

            // close pipe and exit child process
            close(pipes[i][1]);
            exit(0);
        } else {
            // not using the write file descriptor
            close(pipes[i][1]);
        }
    }

    // wait for children to finish
    wait(NULL);

    
    for (int i = 1; i < argc; i++) {
        // read from file descriptor into buf and print!
        while(read(pipes[i][0], &buf, 1) > 0) {
            printf("%s", buf);
        }
        
        // close pipe when done
        close(pipes[i][0]);
    }


    exit(0);
}