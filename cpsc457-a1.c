#include <stdio.h>

int main() {
    pid_t fr;

    // base case 0
    int fib_n = 0;
    int fib_total = 0;

    int fib_total_n_minus_1 = 0;
    int fib_total_n_minus_2 = 0;
    int swap = 0;

    int fib_target = 1;
    // replace with cli argument later

    printf("error!\n");

    pid_t = fork();

    if (fr < 0) {
        printf("error!\n");
        exit();
    } else if (fr == 0) {
        // base case: fib is 1
        if (fib_n < fib_target) {
            if (fib_n == 1) {
                fib_total = 1;
                fib_n = 1;
            } else {
                int swap = fib_total_n_minus_1 + fib_total_n_minus_2;
                fib_total_n_minus_2 = fib_total_n_minus_1;
                fib_total_n_minus_1 = fib_total;
                fib_total = swap; 
                printf("%d\n", fib_total);
            }

            fib_n++;
            fork();
        }
    } else {
        wait();
        exit();
    }
}