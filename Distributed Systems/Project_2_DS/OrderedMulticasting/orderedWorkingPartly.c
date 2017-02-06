
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
int globalId = 0;
int numberNodes = 0;
int array[100], arrayMsg[100];

void setupArray()
{
    int i = 0;
    while(i<100)
    {
        array[i] = -1;
        arrayMsg[i] = -1;
        i++;
    }
}

void printValues()
{
    int i = 0;
    while(i<numberNodes)
    {
        printf("The value of clocks received for the nodes %d are : %d\n",i,array[i]);
        printf("The value in the nodes %d are : %d\n",i,arrayMsg[i]);
        //arrayMsg[i] = -1;
        i++;
    }
}

void initialSetup()
{
    printf("Please enter the number of nodes you want to create in the system\n");
    scanf("%d",&numberNodes);
    printf("You have decided to create : %d nodes\n",numberNodes);
}

void name()
{
    printf("Please provide a unique id for this node starting from 0\n");
    scanf("%d",&globalId);
    printf("You have decided to name this node : %d\n",globalId);
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
    printf("S for sender / R for receiver) :\n");
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
     char message[]="Hello, World from listener!\n";
     char mode;

     struct packet{
        int clock;
        char message;
        int id;
        int numberOfNodes;
     };

     clock = clockLocal();
//     name();

     struct packet sendingPacket;
     sendingPacket.message = 'S';
     sendingPacket.id = globalId;
     sendingPacket.clock = clock;
     sendingPacket.numberOfNodes = numberNodes;
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
    while(j<1000){
         printf("Sending\n");
         clock ++;
         sendingPacket.clock = clock;
         array[globalId] = sendingPacket.clock;
         printf("The value of sendingPacket clock is :%d\n", sendingPacket.clock);
         printf("The value of sendingPacket id is :%d\n", sendingPacket.id);
         if (sendto(sendSocket,&sendingPacket,sizeof(struct packet),0,(struct sockaddr *) &addr1,sizeof(addr1)) < 0) {
               perror("sendto");
               exit(1);
         }
         sleep(1);
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
     //char arrayMsg[10]="";
     //int numberOfNodes = initialSetup(); // this decides the number of nodes that will be connecting apart from the server
     time_t t;
     //int array[numberNodes];
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
     int j = 0, counter = 0;
     int alreadyExists = 0;

     arrayMsg[globalId] = globalId;
     printf("Receiving\n");
     //printf("Counter is %d\n", counter);
     while(counter<numberNodes-1){
         if ((nbytes=recvfrom(fd,&listeningPacket,sizeof(struct packet),0,(struct sockaddr *) &addr,&addrlen)) < 0) {
               perror("recvfrom");
               exit(1);
          }
          printf("The value of listeningPacket clock received is :%d\n", listeningPacket.clock);
          printf("The value of listeningPacket id received is :%d\n", listeningPacket.id);


//         for(int k =0;k<numberNodes;k++)
//         {
               if(arrayMsg[listeningPacket.id]==listeningPacket.id)
               {
                   printf("The value in arrayMsg[%d] is : %d\n",listeningPacket.id, arrayMsg[listeningPacket.id]); //--activate this for debugging
                   alreadyExists = 1 ;
                   printf("The value already exists\n"); //activate this for debugging
               }
               else
               {
                    printf("New value inserted into arrayMsg\n");
                    arrayMsg[listeningPacket.id]=listeningPacket.id;
                    counter++;
                    printf("The value in arrayMsg[%d] is : %d\n",listeningPacket.id, arrayMsg[listeningPacket.id]);
               }
   //      }

         if(listeningPacket.id != globalId) {
            printf("The value of id received in listeningPacket is : %d and Clock received : %d\n", listeningPacket.id,listeningPacket.clock);
            array[listeningPacket.id] = listeningPacket.clock;
            array[globalId] = array[globalId] + 1;
         }
         sleep(1);
         printf("The value of counter is :%d\n", counter);
    }
    // print the values in the array
    printValues();
}

main(int argc, char *argv[])
{
    pthread_t senderThread;
    pthread_t receiverThread;
    int sendSocket,fd;
    initialSetup();
    name();
    setupArray();
    printValues();

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
