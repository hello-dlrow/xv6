#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void sieve(int p[2]) {
    int prime;
    int n;
    close(p[1]); // Close the write end of the pipe in the child process
    if (read(p[0], &prime, sizeof(prime)) == 0) {
        close(p[0]); // Close the read end of the pipe when done
        exit(0);
    }
    printf("prime %d\n", prime);
    
    int next_p[2];
    pipe(next_p);

    if (fork() == 0) {
        sieve(next_p);
    } else {
        close(next_p[0]); // Close the read end of the pipe in the parent process
        while (read(p[0], &n, sizeof(n)) > 0) {
            if (n % prime != 0) {
                write(next_p[1], &n, sizeof(n));
            }
        }
        close(next_p[1]);
        close(p[0]); // Close the read end of the pipe when done
        wait(0);     // Wait for the child process to finish
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    int p[2];
    pipe(p);

    if (fork() == 0) {
        sieve(p);
    } else {
        close(p[0]); // Close the read end of the pipe in the parent process
        for (int i = 2; i <= 35; i++) {
            write(p[1], &i, sizeof(i));
        }
        close(p[1]); // Close the write end of the pipe when done
        wait(0);     // Wait for the child process to finish
        exit(0);
    }
    return 0;
}

