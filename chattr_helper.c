#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/fs.h>

int main (int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Please specify a valid path.");
        exit(-1);
    }

    int i;
    int fd;
    for (i=1; i<argc; i++) {
        char *filename = argv[i];

        if ((fd = open(filename, O_RDONLY)) < 0 &&
            (fd = open(filename, O_RDONLY|O_CREAT, 0600)) < 0) {
            fprintf(stderr, "Cannot open or create file: %s\n", filename);
            exit(-1);
        }

        unsigned long flags;
        ioctl(fd, FS_IOC_GETFLAGS, &flags);
        flags |= FS_APPEND_FL | FS_SYNC_FL;
        if (ioctl(fd, FS_IOC_SETFLAGS, &flags)) {
            fprintf(stderr, "ioctl failed: %s\n", filename);
            exit(-1);
        }

        close(fd);
        chmod(filename, S_IRUSR|S_IWUSR);
    }

    return 0;
}

