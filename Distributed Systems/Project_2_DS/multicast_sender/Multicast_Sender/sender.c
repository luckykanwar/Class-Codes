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

int initialSetup()
{
    int x;
    printf("Please enter the number of listener nodes you want to create\n");
    scanf("%d",&x);
    printf("You have decided to create : %d nodes\n",x);
    return x;
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

main(int argc, char *argv[])
{
     struct sockaddr_in addr;
     int fd, nbytes,addrlen;
     struct ip_mreq mreq;
     char msgbuf[MSGBUFSIZE];
     struct sockaddr_in addr1;
     char flag;
     int sendSocket, cnt1, clock;
     struct ip_mreq mreq1;
     char message[]="";
     char arrayMsg[10]="";
     int x = initialSetup(); // this decides the number of nodes that will be connecting apart from the server
     time_t t;
     int array[1000];


     u_int yes=1;            /*** MODIFICATION TO ORIGINAL */

     struct packet{
        int clock;
        char message;
        int updateFlag; //0 means no update, 1 means update
     };
     struct packet listeningPacket;
     struct packet sendingPacket;

     sendingPacket.message = 'C';
     sendingPacket.updateFlag =0;

     /*Initializing the logical clock*/
     srand((unsigned) time(&t));
     clock=rand()%10;
     printf("This is my clock: %d\n", clock);
     sleep(1);
     sendingPacket.clock = clock;
     /*Initializing the logical clock ends*/

     /* create what looks like an ordinary UDP socket */
     if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
	  perror("socket");
	  exit(1);
     }


/**** MODIFICATION TO ORIGINAL */
    /* allow multiple sockets to use the same PORT number */
    if (setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0) {
       perror("Reusing ADDR failed");
       exit(1);
       }
/*** END OF MODIFICATION TO ORIGINAL */

     /* set up destination address */
     memset(&addr,0,sizeof(addr));
     addr.sin_family=AF_INET;
     addr.sin_addr.s_addr=htonl(INADDR_ANY); /* N.B.: differs from sender */
     addr.sin_port=htons(HELLO_PORT);

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

//    char loopch=0;
//
//    if (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_LOOP,
//                   (char *)&loopch, sizeof(loopch)) < 0) {
//      perror("setting IP_MULTICAST_LOOP:");
//      close(fd);
//      exit(1);
//    }
     /*Sender socket stuff ends*/

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

     int counter =0;
     int sentCounter=0;
     int alreadyExists;
     int loopCounter =0;
     flag = 's';
     int averageClock;
     struct packet syncClocksPacket;
     int exitFlag=0;

     /* now just enter a read-print loop */
     while (1) {
      while(sentCounter<x){
          if(flag=='a')
          {
            /*Call time function here */
            averageClock = setTime(array,arrayMsg,counter, clock);
            printf("The value of averageClock is : %d\n", averageClock);
            sendingPacket.clock = averageClock;
            sendingPacket.message = 'C';
            sendingPacket.updateFlag=1;
            flag = 's';
            exitFlag = 1;
          }

          //printf("Inside the sender loop\n");  --activate this for debugging
          if (sendto(sendSocket,&sendingPacket,sizeof(struct packet),0,(struct sockaddr *) &addr1,sizeof(addr1)) < 0) {
               perror("sendto");
               exit(1);
          }
          clock++;
          //printf("Sent message\n"); --activate this for debugging
          sentCounter++;
          //printf("The value of sentCounter is : %d\n",sentCounter);  --activate this for debugging
          sleep(1);

          if(exitFlag==1)
          {
            return 0;
          }
      }
      sentCounter=0;
      sleep(1);
	  flag = 'r';
      printf("Sender is now becoming a listener\n");

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
         // printf("The clock value received is : %d\n",listeningPacket.clock);   --activate this for debugging
         // printf("The message value received is : %c\n",listeningPacket.message);   --activate this for debugging
         // printf("The update command received is : %d\n",listeningPacket.updateFlag);   --activate this for debugging
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
      //exit(1);
    }
}
