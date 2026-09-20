#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

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
    int pipeidx;

    int    pipes[8][2];
    char   buf[128];

    int i;

    if (argc < 2) exit(0);

    if (argc > 9) argc = 9;

    for (i = 1; i < argc; i++) {
        pipeidx = i - 1;
        if (pipe(pipes[pipeidx]) == -1) {
            exit(-1);
        }
        
        fr = fork();
        if (fr < 0) {
            printf("error!\n");
            exit(-1);
        } else if (fr == 0) {  
            close(pipes[pipeidx][0]);

            fibonacci_n = atoi(argv[i]);

            sprintf(buf, "Child Process (PID %d) F_{%d} = %d\n", getpid(), fibonacci_n, fibonacci(fibonacci_n));
            write(pipes[pipeidx][1], buf, strlen(buf));

            if (close(pipes[pipeidx][1]) == -1) {
                exit(-1);
            }
            exit(0);
        } else {
            if (close(pipes[pipeidx][1]) == -1) {
                exit(-1);
            }
        }
    }

    while (wait(NULL) > 0);

    
    for (i = 0; i < (argc - 1); i++) {
        while(read(pipes[i][0], &buf, 1) > 0) {
            fputs(buf, stdout);
        }
        
        if (close(pipes[i][0]) == -1) {
            exit(-1);
        }
    }


    exit(0);
}