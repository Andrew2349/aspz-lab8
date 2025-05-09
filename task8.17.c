#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int fd = open("example.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        execlp("cat", "cat", NULL);
        perror("execlp");
        exit(1);
    } else {
        write(fd, "Hello from parent\n", 18);
        close(fd);
        wait(NULL);
    }

    return 0;
}
