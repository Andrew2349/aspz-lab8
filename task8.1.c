#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE (1024 * 1024)

int main() {
    int pipefd[2];
    char buffer[BUF_SIZE];
    memset(buffer, 'B', sizeof(buffer));

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }


    fcntl(pipefd[1], F_SETFL, O_NONBLOCK);

    ssize_t total_written = 0;
    while (1) {
        ssize_t count = write(pipefd[1], buffer, sizeof(buffer));
        if (count == -1) {
            perror("write");
            break;
        } else if (count < BUF_SIZE) {
            printf("Partial write occurred! Requested: %ld, Written: %ld\n", (long)BUF_SIZE, (long)count);
            break;
        } else {
            total_written += count;
            printf("Full write: %ld bytes (total: %ld)\n", (long)count, (long)total_written);
        }
    }

    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}

