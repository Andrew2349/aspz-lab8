#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("testfile.bin", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    unsigned char buffer[4];


    if (lseek(fd, 3, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }


    if (read(fd, buffer, 4) != 4) {
        perror("read");
        close(fd);
        return 1;
    }

    printf("Buffer: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    close(fd);
    return 0;
}

