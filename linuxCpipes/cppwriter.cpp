#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
 
#define myfifo "/tmp/myfifo"

int main()
{
    FILE* fd;
    // char * myfifo = "/tmp/myfifo";

    /* create the FIFO (named pipe) */
    //mkfifo(myfifo, 0666);

    /* write "Hi" to the FIFO */
    fd = fopen(myfifo, "w");
    //int n = fd->write("Hi\n", sizeof("Hi\n"));
    int n = fwrite ("Hi\n", sizeof(char), sizeof("Hi\n"),fd);
    printf("%i\n", n);
    /*n = write(fd, "\n", sizeof("\n"));
    printf("%i", n);*/
    //n = *fd->write("My name is.", sizeof("My name is."));
    //printf("%i\n", n);
    /*n= write(fd, "\n", sizeof("\n"));
    printf("%i\n", n);*/
    fclose(fd);

    /* remove the FIFO */
    unlink(myfifo);

    return 0;
}
