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

char initialSetup()
{
    char message;
    printf("Please select a unique name for this node between characters A to Z (Except C, it is reserved)\n");
    scanf("%c",&message);
    return message;
}

main(int argc, char *argv[])
{
     struct sockaddr_in addr;
     int fd, nbytes,addrlen;
     struct ip_mreq mreq;
     char msgbuf[MSGBUFSIZE];
     struct sockaddr_in addr1;
     char flag;
     int sendSocket, cnt1,clock;
     time_t t;
     struct ip_mreq mreq1;
     char message[]="Hello, World from listener!";


     struct packet{
        int clock;
        char message;
        int updateFlag;
     };


     struct packet listeningPacket;
     struct packet sendingPacket;
     //sendingPacket.message = 'S';
     sendingPacket.message = initialSetup();
     sendingPacket.updateFlag = 0;
     u_int yes=1;            /*** MODIFICATION TO ORIGINAL */

    /*Initializing the logical clock*/
     srand((unsigned) time(&t));
     clock=rand()%10;
     printf("This is my clock: %d\n", clock);
     sleep(1);
     sendingPacket.clock = clock; //setting the clock value here
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

//     char loopch=0;
//
//    if (setsockopt(sendSocket, IPPROTO_IP, IP_MULTICAST_LOOP,
//                   (char *)&loopch, sizeof(loopch)) < 0) {
//      perror("setting IP_MULTICAST_LOOP:");
//      close(sendSocket);
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

     /* now just enter a read-print loop */
     while (1) {
	  while(counter<10){
          addrlen=sizeof(addr);
          //printf("Receiver loop entered\n"); --activate this for debugging
          if ((nbytes=recvfrom(fd,&listeningPacket,sizeof(struct packet),0,(struct sockaddr *) &addr,&addrlen)) < 0) {
               perror("recvfrom");
               exit(1);
          }

         // printf("The clock value received is : %d\n",listeningPacket.clock); //--activate this for debugging
         // printf("The message value received is : %c\n",listeningPacket.message); //--activate this for debugging
          clock++;
         // printf("The local clock value is incremented after receiving a message, the new value is : %d\n",clock); //--activate this for debugging
          //printf("The update command received is : %d\n",listeningPacket.updateFlag); --activate this for debugging
          counter++;
          //printf("The counter value is :%d\n",counter); --activate this for debugging
          sleep(1);

          if(listeningPacket.message=='C' && listeningPacket.updateFlag==0){
            flag = 's';
            break;
          }

          if(listeningPacket.message=='C' && listeningPacket.updateFlag==1){
            flag = 's';
            printf("My clock has been updated to : %d\n",listeningPacket.clock);
            //break;
            return 0;
          }
      }
      counter = 0;
      printf("Listener is now becoming a sender\n");
      int sentCounter=0;

      while(sentCounter<2){
          //printf("Inside the sender loop\n"); --activate this for debugging
          //sendingPacket.clock = listeningPacket.clock - clock;
          if (sendto(sendSocket,&sendingPacket,sizeof(struct packet),0,(struct sockaddr *) &addr1,sizeof(addr1)) < 0) {
               perror("sendto");
               exit(1);
          }
          clock++;
         // printf("The value of clock sent is : %d\n",sendingPacket.clock); //--activate this for debugging
         // printf("The value of message sent is : %c\n",sendingPacket.message); //--activate this for debugging
          sentCounter++;
          //printf("The value of sentCounter is : %d\n",sentCounter); --activate this for debugging
          sleep(1);
      }
      //exit(1);
    }
}
