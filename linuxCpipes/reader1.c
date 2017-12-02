#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BUF 1024

int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";
    char buf[MAX_BUF];
    char *b = buf;
    size_t size = 1024;

    /* open, read, and display the message from the FIFO */
    fd = open(myfifo, O_RDONLY);
    while(getline(&b,&size,fd)){
        printf("Received: %s\n",buf);
    }
    // read(fd, buf, MAX_BUF);
    // printf("Received: %s\n", buf);
    // read(fd, buf, MAX_BUF);
    // printf("Received: %s\n", buf);
    close(fd);
    
    return 0;
}
