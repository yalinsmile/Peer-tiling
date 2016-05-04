/* server.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#define MAXLINE 80
#define SERV_PORT 5000
int smap;
int flag=1;
int s=0;//revoke flag
int n=0;//the process id
int table[50];
pthread_t pid1,pid2;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_request = PTHREAD_COND_INITIALIZER;
pthread_rwlock_t rwlock;

//detect the cache consumption 
void *detect(int c)
{
        int i=0; 
        char argStr[80];
        FILE * fp;
        printf("%x\n",(unsigned int)pthread_self());
      
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&has_request, &mutex);
        pthread_mutex_unlock(&mutex);

        while(flag)
        // for(i=0;i<50;i++)
       {
            
           // pthread_rwlock_wrlock(&rwlock);
            system("amplxe-cl -collect-with runsa -knob event-config=L2_LINES_IN.ANY -target-duration-type=short -data-limit=100 -slow-frames-threshold=40 -fast-frames-threshold=100 --duration 1");
            system("amplxe-cl -report hw-events -r /home/zhangyalin/my/r000runsa/ --group-by process -report-out /home/zhangyalin/test_out");
            if(n==0)
                  { system("/home/zhangyalin/my/awk.sh");
                    printf("the wak\n");}
            else {  system("/home/zhangyalin/my/awk1.sh n");
                    printf("the id in awk1 is:%d\n",n);}
            system("rm -rf /home/zhangyalin/my/r000runsa");
            fp=fopen("/home/zhangyalin/out_put","rt");
            fgets(argStr,80,fp);
            smap=atoi(argStr);
            
            table[i++%5]=smap;
           // pthread_rwlock_unlock(&rwlock);
            printf("the id is:%d\n",n);
            printf("%x is:%d\n",(unsigned int)pthread_self(), smap);
        }
 
        pthread_exit(NULL);
}

//handle the client program
void *con_client(void *arg)
{
        int threadfd=(int)arg;
	char buf[MAXLINE];
        char str[INET_ADDRSTRLEN];
        char string[INET_ADDRSTRLEN];
        char str1[INET_ADDRSTRLEN];
        int i;
        int sum=0;
        int f=0;
        void *thread_result;
	recv(threadfd, buf, MAXLINE,0);
        printf("the condition is:%s\n",buf);
       
        if(!strcmp(buf,"start helper thread"))
        {
	      pthread_cond_signal(&has_request);
              s=1;
              strcpy(str,"OK");
              send(threadfd, str, strlen(str),0);
              recv(threadfd, string, MAXLINE,0);
              n=atoi(string);
              printf("the id in server is:%d\n",n);
        } 
        else if(!strcmp(buf,"kill helper thread"))
        {
              flag=0;  //kill the helper thread
        }
        else if(!strcmp(buf,"instant"))
        {
	      if(s==0)//the loop don't hava 't',only has the instant mode
              {
                     pthread_cond_signal(&has_request);  //revoke the helper thread
                     sleep(6);
                     flag=0;
              }
              else {
//              sleep(10);
              printf("I am in client\n");
              }
              f=smap;
              flag=0;
        }
        else 
              if(!strcmp(buf,"average"))
              {       
          //           sleep(10);
               //      flag=0;
                     //only get the value ,the helper thread is still alive
             	     for(i=0;i<5;i++)
                     {
                           sum+=table[i];
                     }
                     f=sum/5;
              }
              else 
              {
                     strcpy(str,"the server don't deal with the function");
                     send(threadfd, str, strlen(str),0);
              }
	             
        if(!strcmp(buf,"instant")||!strcmp(buf,"average")){
       		 printf("the send data is:  %d\n",f);
        	 sprintf(str1, "%d", f);
       		 send(threadfd, str1, strlen(str1),0);
	}
        close(threadfd);
        pthread_exit(NULL);

}
       
 
int main(void)
{ 
        pthread_t child_thread[MAXLINE];
	struct sockaddr_in servaddr, cliaddr; 
	socklen_t cliaddr_len;
	int listenfd, connfd;
        int index=0;
       // char buf[MAXLINE];
        pthread_create(&pid1,NULL,detect,0);//start the helper thread,but in passive mode
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(SERV_PORT); 
	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)); 
	listen(listenfd, 20); 
	printf("Accepting connections ...\n"); 
	
	while (1) 
	{ 	    
		cliaddr_len = sizeof(cliaddr); 
		connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&cliaddr_len); 
                pthread_create(&child_thread[index++],NULL,con_client, (void*)connfd) ;
            
		//printf("received from %s at PORT %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port)); 
		//printf("received  %s  number %d\n",buf,n);
		/*for (i = 0; i < n; i++)
		buf[i] = toupper(buf[i]);
		write(connfd, buf, n); */
		//close(connfd); 
	}
	close(listenfd);
}
