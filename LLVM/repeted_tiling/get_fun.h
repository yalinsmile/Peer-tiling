#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <process.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define MAXLINE 80
#define SERV_PORT 5000

int getid()
{
        return getpid();
}

int get_start(int id)
{
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

int set_end()
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

double get_ins_comsuption()
{
        struct sockaddr_in servaddr;
        char buf[MAXLINE];
        int sockfd, n;
        double map;
        char *str="instant";
       // char *str="average";
        printf("the str is:%s\n",str);
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        inet_aton("127.0.0.1", &servaddr.sin_addr);
        servaddr.sin_port = htons(SERV_PORT);
        connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
        send(sockfd, str, strlen(str),0);
        recv(sockfd, buf, MAXLINE,0);//can't get the number
        map=atoi(buf);
        printf("the data is:%lf\n",map);
        close(sockfd);
       // return 138;
        int real=pow(10,5);
        return map/real;
}

double get_ave_comsuption()
{
        struct sockaddr_in servaddr;
        char buf[MAXLINE];
        int sockfd, n;
        int map;
        char *str="average";
        printf("the str is:%s\n",str);
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        inet_aton("127.0.0.1", &servaddr.sin_addr);
        servaddr.sin_port = htons(SERV_PORT);
        connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
        send(sockfd, str, strlen(str),0);
        recv(sockfd, buf, MAXLINE,0);//can't get the number
        map=atoi(buf);
        printf("the data is:%d\n",map);
        close(sockfd);
        int real=pow(10,5);
        return map/real;
}

/*
int get_comsuption()
{
   int a;int b;
   a=128;
   b=54;
   return a-b;
}
*/
int get_tile_size(double a,int b)
{
   double c;
   printf("the data is:%lf\n",a);
   if(a<1.2)
   c=-77.665*a+517.95;
   else c=224;
   printf("the tile-size is:%lf\n",c);
   int d=c/32;
   printf("the scale is:%d\n",d);
   printf("the real size is:%d\n",d*32);
   if(abs(d*32-c)<abs((d+1)*32-c))
     return d*32;
   else
   return (d+1)*32;
}


double ave(int t)
{
   if (t==0)
      return get_ins_comsuption();
   else return get_ave_comsuption();
}
