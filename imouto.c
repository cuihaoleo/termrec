#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/fs.h>

int main (int argc, char* argv[]) {
    if (argc < 3) {
showhelp:
        fprintf(stderr, "Usage: %s [immutable|appendonly] <files>\n", argv[0]);
        exit(-1);
    }

    int addflags, blkflags;
    if (!strcmp(argv[1], "immutable"))
        addflags = FS_IMMUTABLE_FL,
        blkflags = FS_APPEND_FL | FS_SYNC_FL;
    else if (!strcmp(argv[1], "appendonly"))
        addflags = FS_APPEND_FL | FS_SYNC_FL,
        blkflags = FS_IMMUTABLE_FL;
    else
        goto showhelp;

    int i;
    for (i=2; i<argc; i++) {
        char *filename = argv[i];
        int fd;

        if ((fd = open(filename, O_RDONLY)) < 0 &&
            (fd = open(filename, O_RDONLY|O_CREAT, 0600)) < 0) {
            fprintf(stderr, "Cannot open or create file: %s\n", filename);
            continue;
        }

        unsigned long flags;
        ioctl(fd, FS_IOC_GETFLAGS, &flags);

        flags &= ~blkflags;
        flags |= addflags;

        if (ioctl(fd, FS_IOC_SETFLAGS, &flags))
            fprintf(stderr, "ioctl failed: %s\n", filename);

        close(fd);
    }

    return 0;
}

