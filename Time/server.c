#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define PORT 37
#define BUF_SIZE 4096
#define QUEUE_SIZE 10

int main(int argc, char * argv[]) {
    int s, b, l, fd, sa, bytes, on = 1;
    
    struct sockaddr_in channel;
    memset(&channel, 0, sizeof(channel));
    channel.sin_family = AF_INET;
    channel.sin_addr.s_addr = htonl(INADDR_ANY);
    channel.sin_port = htons(PORT);

    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s < 0) {
        printf("socket failed\n");
        return 1;
    }
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char * ) &on, sizeof(on));

    printf(getsockname(s, (struct sockaddr *) &channel, &b));

    b = bind(s, (struct sockaddr *) &channel, sizeof(channel));
    if (b < 0) {
        printf("bind failed\n");
        return 1;
    }

    l = listen(s, QUEUE_SIZE);
    if (l < 0) {
        printf("listen failed\n");
        return 1;
    }

    printf("okej\n");

    while (1) {
        char buf[BUF_SIZE];
        sa = accept(s, 0, 0);
        if (sa < 0) {
            printf("accept failed\n");
            return 1;
        }
        printf("nu fick jag inte kuk\n");
        read(sa, buf, BUF_SIZE);
        printf("nu fick jag kuk\n");

        time_t curtime;
        time(&curtime);

        char* nuvarande_tid = ctime(&curtime);

        write(sa, nuvarande_tid, strlen(nuvarande_tid));
        close(fd);
        close(sa);
    }
}