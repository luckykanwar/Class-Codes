#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include<pthread.h>


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

char mode()
{
    char mode;
    printf("Do you want this process to be the first sender ? (y/n) : ");
    scanf("%c",&mode);
    return mode;
}

int setTime(int array[], char arrayMsg[], int counter, int localClock){
    /*Calculate average time here*/
    int averageClock =0;
    for(int i=0; i<counter;i++)
    {
        printf("The values in the array are: %d\n",array[i]);
    }
    for(int i=0; i<counter;i++)
    {
        averageClock = averageClock + array[i];
    }
    averageClock = averageClock/counter;
    return averageClock;
}

/* This receive function is run by this thread */
void receivePackets(int fd)
{

        struct packet{
        int clock;
        char message;
        int id; //this is just residual stuff for now
};


    int counter =0;
    int sentCounter=0;
    int alreadyExists;
    int loopCounter =0;
    char flag = 's';
    int averageClock;
    int exitFlag=0;
    sentCounter=0;
    sleep(1);
	flag = 'r';
    printf("Sender is now becoming a listener\n");
    int x = initialSetup(); // this decides the number of nodes that will be connecting apart from the server;
    int array[x];
    char arrayMsg[]="";
    struct sockaddr_in addr;
    int nbytes,addrlen;
     struct ip_mreq mreq;
     struct sockaddr_in addr1;
     u_int yes=1;
     struct packet listeningPacket;

     int sendSocket, cnt1, clock;
     struct ip_mreq mreq1;
/*--------------------------------------------------------------------------------------------------------------*/
//     /* Receiver socket starts here */
//     if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
//	  perror("socket");
//	  exit(1);
//     }

    /* allow multiple sockets to use the same PORT number */
    if (setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0) {
       perror("Reusing ADDR failed");
       exit(1);
       }

     /* set up destination address */
     memset(&addr,0,sizeof(addr));
     addr.sin_family=AF_INET;
     addr.sin_addr.s_addr=htonl(INADDR_ANY); /* N.B.: differs from sender */
     addr.sin_port=htons(HELLO_PORT);

     /* bind to receive address */
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
    /*Receiver socket ends here*/

/*--------------------------------------------------------------------------------------------------------------*/
	  //while(loopCounter<3){
	while(counter<x){
          alreadyExists = 0;
          addrlen=sizeof(addr);
          //printf("Receiver loop entered\n"); --activate this for debugging
          if ((nbytes=recvfrom(fd,&listeningPacket,sizeof(struct packet),0,(struct sockaddr *) &addr,&addrlen)) < 0) {
               perror("recvfrom");
               exit(1);
          }
          clock++;
          printf("The clock value received is : %d\n",listeningPacket.clock);   //--activate this for debugging
          printf("The message value received is : %c\n",listeningPacket.message);   //--activate this for debugging
          printf("The update command received is : %d\n",listeningPacket.id);   //--activate this for debugging
          //counter++;
          sleep(1);

              for(int k =0;k<x;k++)
              {
                if(arrayMsg[k]==listeningPacket.message || listeningPacket.message=='C')
                {
                    //printf("The value in arrayMsg is : %c\n",arrayMsg[k]); --activate this for debugging
                    alreadyExists = 1 ;
                    //printf("The value already exists\n"); --activate this for debugging
                    break;
                }
              }

              if(alreadyExists!=1){
                arrayMsg[counter]=listeningPacket.message;
                array[counter] = listeningPacket.clock;
                counter++;
               // printf("The counter value is :%d\n",counter); --activate this for debugging
              }

//          if(listeningPacket.message=='S'){
//            flag = 's';
//            break;
//          }
            if(counter == x)
            {
                flag='a';
                break;
            }
            loopCounter++;
            flag ='s';
    }
}

int main(int argc, char *argv[])
{
/*--------------------------------------------------------------------------------------------------------------*/
    /*Initial setup of variables*/
     struct sockaddr_in addr;
     int fd, nbytes,addrlen;
     struct ip_mreq mreq;
     struct sockaddr_in addr1;
     char flag;
     int sendSocket, cnt1, clock;
     struct ip_mreq mreq1;
     char message[]="";
     char arrayMsg[]="";
     int x = initialSetup(); // this decides the number of nodes that will be connecting apart from the server
     time_t t;
     int array[x];

     u_int yes=1;

     struct packet{
        int clock;
        char message;
        int id; //this is just residual stuff for now
     };

     struct packet listeningPacket;
     struct packet sendingPacket;
     sendingPacket.message = 'S';
     sendingPacket.id = name();
/*--------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------*/
     /*Initializing the logical clock to 0*/
     clock=0;
     printf("My clock is started at value : %d\n", clock);
     sleep(1);
     sendingPacket.clock = clock;
     /*Initializing the logical clock ends*/
/*--------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------*/
     /*Sender socker stuff starts*/
     if ((sendSocket=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
	  perror("socket");
	  exit(1);
     }

     /* set up destination address */
     memset(&addr1,0,sizeof(addr1));
     addr1.sin_family=AF_INET;
     addr1.sin_addr.s_addr=inet_addr(HELLO_GROUP);
     addr1.sin_port=htons(HELLO_PORT);
     /*Sender socket stuff ends*/
/*--------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------*/
//     /* Receiver socket starts here */
//     if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
//	  perror("socket");
//	  exit(1);
//     }
//
//    /* allow multiple sockets to use the same PORT number */
//    if (setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0) {
//       perror("Reusing ADDR failed");
//       exit(1);
//       }
//
//     /* set up destination address */
//     memset(&addr,0,sizeof(addr));
//     addr.sin_family=AF_INET;
//     addr.sin_addr.s_addr=htonl(INADDR_ANY); /* N.B.: differs from sender */
//     addr.sin_port=htons(HELLO_PORT);
//
//     /* bind to receive address */
//     if (bind(fd,(struct sockaddr *) &addr,sizeof(addr)) < 0) {
//	  perror("bind");
//	  exit(1);
//     }
//
//     /* use setsockopt() to request that the kernel join a multicast group */
//     mreq.imr_multiaddr.s_addr=inet_addr(HELLO_GROUP);
//     mreq.imr_interface.s_addr=htonl(INADDR_ANY);
//     if (setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0) {
//	  perror("setsockopt");
//	  exit(1);
//     }
//    /*Receiver socket ends here*/
//
///*--------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------*/

     int counter =0;
     int sentCounter=0;
     int alreadyExists;
     int loopCounter =0;
     flag = 's';
     int averageClock;
     int exitFlag=0;
     pthread_t thread;

     /* The main program logic starts here */
     while (1) {
      if('y'=='y'){
        while(sentCounter<x){
//          if(flag=='a')
//          {
//            /*Call time function here */
//            averageClock = setTime(array,arrayMsg,counter, clock);
//            printf("The value of averageClock is : %d\n", averageClock);
//            sendingPacket.clock = averageClock;
//            sendingPacket.message = 'C';
//            sendingPacket.updateFlag=1;
//            flag = 's';
//            exitFlag = 1;
//          }
          sendingPacket.clock++;
          //printf("Inside the sender loop\n");  --activate this for debugging
          if (sendto(sendSocket,&sendingPacket,sizeof(struct packet),0,(struct sockaddr *) &addr1,sizeof(addr1)) < 0) {
               perror("sendto");
               exit(1);
          }
          printf("Sent message\n"); //--activate this for debugging
          //printf("The value of clock is now : %d", sendingPacket.clock);
          sentCounter++;
          //printf("The value of sentCounter is : %d\n",sentCounter);  --activate this for debugging
          sleep(1);

//          if(exitFlag==1)
//          {
//            return 0;
//          }
      }
    }
      pthread_create(thread, NULL, receivePackets, fd);
//      sentCounter=0;
//      sleep(1);
//	  flag = 'r';
//      printf("Sender is now becoming a listener\n");

	  //while(loopCounter<3){
//	  while(counter<x){
//          alreadyExists = 0;
//          addrlen=sizeof(addr);
//          //printf("Receiver loop entered\n"); --activate this for debugging
//          if ((nbytes=recvfrom(fd,&listeningPacket,sizeof(struct packet),0,(struct sockaddr *) &addr,&addrlen)) < 0) {
//               perror("recvfrom");
//               exit(1);
//          }
//          clock++;
//         // printf("The clock value received is : %d\n",listeningPacket.clock);   --activate this for debugging
//         // printf("The message value received is : %c\n",listeningPacket.message);   --activate this for debugging
//         // printf("The update command received is : %d\n",listeningPacket.updateFlag);   --activate this for debugging
//          //counter++;
//          sleep(1);
//
//              for(int k =0;k<x;k++)
//              {
//                if(arrayMsg[k]==listeningPacket.message || listeningPacket.message=='C')
//                {
//                    //printf("The value in arrayMsg is : %c\n",arrayMsg[k]); --activate this for debugging
//                    alreadyExists = 1 ;
//                    //printf("The value already exists\n"); --activate this for debugging
//                    break;
//                }
//              }
//
//              if(alreadyExists!=1){
//                arrayMsg[counter]=listeningPacket.message;
//                array[counter] = listeningPacket.clock;
//                counter++;
//               // printf("The counter value is :%d\n",counter); --activate this for debugging
//              }
//
////          if(listeningPacket.message=='S'){
////            flag = 's';
////            break;
////          }
//            if(counter == x)
//            {
//                flag='a';
//                break;
//            }
//            loopCounter++;
//            flag ='s';
//      }
      //exit(1);
        }

}
