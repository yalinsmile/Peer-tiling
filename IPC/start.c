/* client.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define MAXLINE 80
#define SERV_PORT 5000


int main(void)
{
        /* 
	struct sockaddr_in servaddr;
	char buf[MAXLINE]; 
        char str1[80];
	int sockfd, n;
	int map;
        int id=5000;
        char *str="start helper thread";
        //char *str="average";
	/*if (argc != 2) 
	{ 
		fputs("usage: ./client message\n", stderr); 
		exit(1);		
	} 
	str = argv[1];*/
        /*
	printf("the str is:%s\n",str);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET;
	inet_aton("127.0.0.1", &servaddr.sin_addr); 
	servaddr.sin_port = htons(SERV_PORT); 
	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
        send(sockfd, str, strlen(str),0);
        recv(sockfd, buf, MAXLINE,0);
        sprintf(str1, "%d", id);
        send(sockfd, str1, strlen(str1),0);
        /*
	recv(sockfd, buf, MAXLINE,0);//can't get the number
        map=atoi(buf);
	printf("the data is:%d\n",map);
        */
       // printf("received from %s\n",buf);	
	//write(sockfd, str, strlen(str));
	//n = read(sockfd, buf, MAXLINE); 
	//printf("Response from server:\n"); 
	//write(STDOUT_FILENO, buf, n);
	//printf("received from %s at PORT %d\n",buf,n);
        /*
	close(sockfd);
	return 0;*/
        int id=5000;
        struct sockaddr_in servaddr;
        char buf[MAXLINE];
        char str1[80];
        int sockfd, n;
        int map;
        char *str="start helper thread";
        printf("the str is:%s\n",str);
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        inet_aton("127.0.0.1", &servaddr.sin_addr);
        servaddr.sin_port = htons(SERV_PORT);
        connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
        send(sockfd, str, strlen(str),0);
        recv(sockfd, buf, MAXLINE,0);
        sprintf(str1, "%d", id);
        send(sockfd, str1, strlen(str1),0);
         close(sockfd);
        return 0;
}
