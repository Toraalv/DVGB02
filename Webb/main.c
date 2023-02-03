#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define PORT 8080
#define BUF_SIZE 4096
#define QUEUE_SIZE 10

char* getURLfromHTTPheader(char* buf);
char* getContentTypeFromURL(char* buf);

int main(int argc, char * argv[]) {
    int s, b, l, fd, sa, bytes, on = 1;
    
    struct sockaddr_in channel;
    memset(&channel, 0, sizeof(channel));
    channel.sin_family = AF_INET;
    channel.sin_addr.s_addr = htonl(INADDR_ANY);
    channel.sin_port = htons(PORT);

    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s < 0) {
        printf("socket failed\n");
        return 1;
    }
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char * ) &on, sizeof(on));

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

    while (1) {
        char buf[BUF_SIZE];
        sa = accept(s, 0, 0);
        if (sa < 0) {
            printf("accept failed\n");
            return 1;
        }
        read(sa, buf, BUF_SIZE);

        char *file = getURLfromHTTPheader(buf);
        fd = open(file, O_RDONLY);
        if (fd < 0) {
            write(sa, "HTTP/1.1 404 Not Found\r\nServer: Saba\r\nContent-Length: 13\r\nContent-Type: text/plain\r\n\r\n404 Not Found", 100);
            close(fd);
            close(sa);
            continue;
        }
        off_t fsize = lseek(fd, 0, SEEK_END);
        lseek(fd, 0, SEEK_SET);
        char* header;
        sprintf(header, "HTTP/1.1 200 OK\r\nServer: Saba\r\nContent-Length: %lld\r\nContent-Type: %s\r\n\r\n", fsize, getContentTypeFromURL(file));
        write(sa, header, strlen(header));
        while (1) { // skicka filens data
            bytes = read(fd, buf, BUF_SIZE);
            if (bytes <= 0) {
                break;
            }
            write(sa, buf, bytes);
        }
        close(fd);
        close(sa);
    }
}

char* getURLfromHTTPheader(char* buf) {
    char* finalURL = strstr(buf, "/");
    // ++ tar bort det första snedstrecket (alternativt) ¯\_(ツ)_/¯ 
    return strtok(++finalURL, " ");
}

char* getContentTypeFromURL(char* filepath) {
    char* string = strstr(filepath, ".");

    if (!strcmp(string, ".png"))
        return "image/png";
    else if (!strcmp(string, ".jpg"))
        return "image/jpeg";
    else if (!strcmp(string, ".html"))
        return "text/html"; 
    else
        return "application/octet-stream";
}