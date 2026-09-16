#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

    if (argc < 2) exit(0);

    for (int i = 1; i < argc; i++) {
        fr = fork();
        if (fr < 0) {
            printf("error!\n");
            exit(-1);
        } else if (fr == 0) {  
            fibonacci_n = atoi(argv[i]);
            printf("Child Process (PID %d) F_{%d} = %d\n", getpid(), fibonacci_n, fibonacci(fibonacci_n));
            exit(0);
        }
    }
    
    wait();
    exit(0);
}