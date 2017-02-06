#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#define HELLO_PORT 12345
#define HELLO_GROUP "225.0.0.37"
#define MSGBUFSIZE 256

int initialSetup()
{
    int x;
    printf("Please enter the number of nodes you want to create in the system\n");
    scanf("%d",&x);
    printf("You have decided to create : %d nodes\n",x);
    return x;
}

int name()
{
    int nameID;
    printf("Please provide a unique id for this node starting from 0\n");
    scanf("%d",&nameID);
    printf("You have decided to name this node : %d\n",nameID);
    return nameID;
}

int clockLocal()
{
    /*--------------------------------------------------------------------------------------------------------------*/
     /*Initializing the logical clock to 0*/
     int clockLocal=0;
     printf("My clock is started at value : %d\n", clockLocal);
     sleep(1);
     return clockLocal;
     /*Initializing the logical clock ends*/
    /*--------------------------------------------------------------------------------------------------------------*/
}

char runMode()
{
    char mode;
    printf("Enter the mode in which you want to start this node\n");
    printf("S for sender / R for receiver) :");
    scanf("%c",&mode);
    if(mode == 'S')
        printf("You have decided to start in Sender mode\n");
    else
        printf("You have decided to start in Receiver mode\n");
}

void sender(int sendSocket){
     struct sockaddr_in addr;
     int fd, nbytes,addrlen;
     struct ip_mreq mreq;
     char msgbuf[MSGBUFSIZE];
     struct sockaddr_in addr1;
     char flag;
     int cnt1,clock;
     time_t t;
     struct ip_mreq mreq1;
     char message[]="Hello, World from listener!";
     char mode;
     int numberOfNodes = initialSetup();

     struct packet{
        int clock;
        char message;
        int id;
        int numberOfNodes;
     };

     clock = clockLocal();

     struct packet sendingPacket;
     sendingPacket.message = 'S';
     sendingPacket.id = name();
     sendingPacket.clock = clock;
     sendingPacket.numberOfNodes = numberOfNodes;
     u_int yes=1;

     /* set up destination address */
     memset(&addr1,0,sizeof(addr1));
     addr1.sin_family=AF_INET;
     addr1.sin_addr.s_addr=inet_addr(HELLO_GROUP);
     addr1.sin_port=htons(HELLO_PORT);

     int j =0;

//     printf("Starting the node");
//     mode = runMode();
//     if(runMode == 'S')
//     {
//        sleep(5);
//     }

//     while(j<numberOfNodes){
    while(j<100){
         printf("Sending\n");
         clock ++;
         sendingPacket.clock = clock;
         printf("The value of sendingPacket clock is :%d\n", sendingPacket.clock);
         if (sendto(sendSocket,&sendingPacket,sizeof(struct packet),0,(struct sockaddr *) &addr1,sizeof(addr1)) < 0) {
               perror("sendto");
               exit(1);
         }
         sleep(2);
     j++;
    }
}

void receiver(int * fd){
     struct sockaddr_in addr;
     int nbytes,addrlen;
     struct ip_mreq mreq;
     char msgbuf[MSGBUFSIZE];
     struct sockaddr_in addr1;
     char flag;
     int sendSocket, cnt1, clock;
     struct ip_mreq mreq1;
     char message[]="";
     char arrayMsg[10]="";
     //int numberOfNodes = initialSetup(); // this decides the number of nodes that will be connecting apart from the server
     time_t t;
     int array[100];
     u_int yes=1;

     struct packet{
        int clock;
        char message;
        int id;
        int numberOfNodes;
     };

     /* allow multiple sockets to use the same PORT number */
    if (setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0) {
       perror("Reusing ADDR failed");
       exit(1);
       }

     memset(&addr,0,sizeof(addr));
     addr.sin_family=AF_INET;
     addr.sin_addr.s_addr=htonl(INADDR_ANY); /* N.B.: differs from sender */
     addr.sin_port=htons(HELLO_PORT);

     if (bind(fd,(struct sockaddr *) &addr,sizeof(addr)) < 0) {
	  perror("bind");
	  exit(1);
     }

     /* use setsockopt() to request that the kernel join a multicast group */
     mreq.imr_multiaddr.s_addr=inet_addr(HELLO_GROUP);
     mreq.imr_interface.s_addr=htonl(INADDR_ANY);
     if (setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0) {
	  perror("setsockopt");
	  exit(1);
     }

     struct packet listeningPacket;

     int j =0;

     while(1){
         //printf("Receiving\n");
         if ((nbytes=recvfrom(fd,&listeningPacket,sizeof(struct packet),0,(struct sockaddr *) &addr,&addrlen)) < 0) {
               perror("recvfrom");
               exit(1);
          }
         //if(listeningPacket.message !='S') {
         printf("The value of id received in listeningPacket is : %d and Clock received : %d\n", listeningPacket.id,listeningPacket.clock);
         //printf("The value of Clock received in listeningPacket is : %d\n", listeningPacket.clock);
         //}
         sleep(1);
     j++;
    }
}

main(int argc, char *argv[])
{
    pthread_t senderThread;
    pthread_t receiverThread;
    int sendSocket,fd;

    /*Sender socker stuff starts*/
     if ((sendSocket=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
	  perror("socket");
	  exit(1);
     }
     /*Sender socket stuff ends*/

     /*Receiver socket stuff starts*/
     if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
	  perror("socket");
	  exit(1);
     }
     /*Receiver socket stuff ends*/

    pthread_create(&senderThread, NULL, sender, sendSocket);

    pthread_create(&receiverThread, NULL, receiver, fd);

    pthread_join(senderThread, NULL);
    pthread_join(receiverThread, NULL);
//    printf("Reached here receiver\n");
//    printf("The value of fd is now : %d\n",fd);

}
