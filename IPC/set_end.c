#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#define MAXLINE 80
#define SERV_PORT 5000


int main()
{
       struct sockaddr_in servaddr;
        char buf[MAXLINE];
        int sockfd, n;
        int map;
        char *str="kill helper thread";
        printf("the str is:%s\n",str);
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        inet_aton("127.0.0.1", &servaddr.sin_addr);
        servaddr.sin_port = htons(SERV_PORT);
        connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
        send(sockfd, str, strlen(str),0);
         close(sockfd);
        return 0;
}

