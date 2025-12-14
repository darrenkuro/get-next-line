#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void) {
    int fd1 = open("examples/input1.txt", O_RDONLY);
    int fd2 = open("examples/input2.txt", O_RDONLY);
    int fd3 = open("examples/input3.txt", O_RDONLY);

    if (fd1 < 0 || fd2 < 0 || fd3 < 0) {
        perror("open");
        return 1;
    }

    char *l1 = NULL;
    char *l2 = NULL;
    char *l3 = NULL;

    while (1) {
        l1 = get_next_line(fd1);
        l2 = get_next_line(fd2);
        l3 = get_next_line(fd3);

        if (!l1 && !l2 && !l3)
            break;

        if (l1) {
            printf("fd1: %s", l1);
            free(l1);
        }
        if (l2) {
            printf("fd2: %s", l2);
            free(l2);
        }
        if (l3) {
            printf("fd3: %s", l3);
            free(l3);
        }
    }

    close(fd1);
    close(fd2);
    close(fd3);
    return 0;
}
