#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";

    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);

    /* write "Hi" to the FIFO */
    fd = open(myfifo, O_WRONLY);
    int n =  write(fd, "Hi\n", sizeof("Hi\n"));
    printf("%i\n", n);
    /*n = write(fd, "\n", sizeof("\n"));
    printf("%i", n);*/
    n = write(fd, "My name is.", sizeof("My name is."));
    printf("%i\n", n);
    /*n= write(fd, "\n", sizeof("\n"));
    printf("%i\n", n);*/
    close(fd);

    /* remove the FIFO */
    unlink(myfifo);

    return 0;
}
