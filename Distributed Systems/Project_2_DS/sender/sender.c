
/*
 * sender.c -- multicasts "hello, world!" to a multicast group once a second
 *
 * Antony Courtney,	25/11/94
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>


#define HELLO_PORT 12345
#define HELLO_GROUP "225.0.0.37"
#define MSGBUFSIZE 256

main(int argc, char *argv[])
{
     struct sockaddr_in addr;
     int fd, nbytes, cnt, addrlen, newsocket,newsocket1;
     struct ip_mreq mreq;
     char *message="Hello";
     char msgbuf[MSGBUFSIZE];

     /* create what looks like an ordinary UDP socket */
     if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
	  perror("socket");
	  exit(1);
     }

     /* set up destination address */
     memset(&addr,0,sizeof(addr));
     addr.sin_family=AF_INET;
     addr.sin_addr.s_addr=inet_addr(HELLO_GROUP);
     addr.sin_port=htons(HELLO_PORT);

     int counter = rand();
     int increaseCounter = rand()%10;

     /* now just sendto() our destination! */
     while (1) {

             printf("Inside the sender function\n");
             sendto(fd,"Hello from sender!",sizeof("Hello from sender!"),0,(struct sockaddr *) &addr, sizeof(addr));

             newsocket=socket(AF_INET,SOCK_DGRAM,0);
             if((nbytes=recvfrom(newsocket,msgbuf,MSGBUFSIZE,0,
			       (struct sockaddr *) &addr,&addrlen)) < 0) {
			       printf("Something is wrong here !\n");
                   perror("recvfrom");
                   exit(1);
              }
             else {
                puts(msgbuf);
                counter = counter + increaseCounter;
                printf("Local counter in sender is : %d\n", counter);
                printf("Local counter in sender is : %d\n", counter%10);
              }
             if(strcmp(msgbuf,"send_time")== 0)
              {
                  printf("Inside the sender function");
                  newsocket1=socket(AF_INET,SOCK_DGRAM,0);
                  if (sendto(fd,message,sizeof(message),0,(struct sockaddr *) &addr,
                         sizeof(addr)) < 0) {
                     perror("sendto");
                     exit(1);
                  }
                  counter = counter + increaseCounter;
                  puts(message);
              }
      }
}
