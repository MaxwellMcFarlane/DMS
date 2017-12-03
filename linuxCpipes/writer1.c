#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    FILE* fd;
    char * myfifo = "/tmp/myfifo";

    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);

    /* write "Hi" to the FIFO */
    fd = fopen(myfifo,"r+");
    fprintf(fd, "Hi");
    fclose(fd);

    /* remove the FIFO */
    unlink(myfifo);

    return 0;
}
