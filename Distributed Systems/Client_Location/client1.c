#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int MAX_RECV_BUF = 256;
int MAX_SEND_BUF = 256;
void error(char *msg)
{
    perror(msg);
    exit(0);
}

int send_action_to_server(int sockfd, char* action)
{
    char send_str [MAX_SEND_BUF]; /* message to be sent to server*/
    int f; /* file handle for receiving file*/
    ssize_t sent_bytes, rcvd_bytes, rcvd_file_size;
    int recv_count; /* count of recv() calls*/
    char recv_str[MAX_RECV_BUF]; /* buffer to hold received data */
    size_t send_strlen; /* length of transmitted string */
    printf("Reached send action function\n");
    sprintf(send_str, "%s\n", action); /* add CR/LF (new line) */
    send_strlen = strlen(send_str); /* length of message to be transmitted */

    if( (sent_bytes = send(sockfd, action, send_strlen, 0)) < 0 ) {
        perror("send error");
        return -1;
    }
}

//Code for uploading file to server
int send_file(int sockfd, char* file_name)
{
    unsigned char buff[256]= {0};
    int nread;
    bzero(buff,256);
    char send_str [MAX_SEND_BUF]; /* message to be sent to server*/
    int f; /* file handle for receiving file*/
    ssize_t sent_bytes, rcvd_bytes, rcvd_file_size;
    int recv_count; /* count of recv() calls*/
    char recv_str[MAX_RECV_BUF]; /* buffer to hold received data */
    size_t send_strlen; /* length of transmitted string */
    sprintf(send_str, "%s\n", file_name);
    send_strlen = strlen(send_str);

    if( (sent_bytes = send(sockfd, file_name, send_strlen, 0)) < 0 ) {
        perror("send error");
        return -1;
    }

    // Open the file that we wish to transfer
    FILE *fp = fopen(file_name,"rb"); //take a sample file
    if(fp==NULL)
    {
        printf("File open error\n");
        return 1;
    }
    else
    {
        printf("File opened successfully\n");
    }

    while(1)
    {
        // First read file in chunks of 255 bytes
        nread = fread(buff,1,255,fp);
        printf("Bytes read %d \n", nread);
        printf("%s\n", buff);
        // If read was success, send data.
        if(nread > 0)
        {
            printf("Sending \n");
            write(sockfd, buff, nread);
        }

        //There is something tricky going on with read .. Either there was error, or we reached end of file.
        if (nread < 255)
        {
            if (feof(fp))
                printf("End of file\n");
            if (ferror(fp))
                printf("Error reading\n");
            break;
        }
    }
    fclose(fp);
}

//Code for downloading file from server
int recv_file(int sock, char* file_name)
{
    char send_str [MAX_SEND_BUF]; /* message to be sent to server*/
    int f; /* file handle for receiving file*/
    ssize_t sent_bytes, rcvd_bytes, rcvd_file_size;
    int recv_count; /* count of recv() calls*/
    char recv_str[MAX_RECV_BUF]; /* buffer to hold received data */
    size_t send_strlen; /* length of transmitted string */
    sprintf(send_str, "%s\n", file_name); /* add CR/LF (new line) */
    send_strlen = strlen(send_str); /* length of message to be transmitted */

    if( (sent_bytes = send(sock, file_name, send_strlen, 0)) < 0 ) {
        perror("send error");
        return -1;
    }

    /* attempt to create file to save received data. 0644 = rw-r--r-- */
    if ( (f = open(file_name, O_WRONLY|O_CREAT, 0644)) < 0 )
    {
        perror("error creating file");
        return -1;
    }

    recv_count = 0; /* number of recv() calls required to receive the file */
    rcvd_file_size = 0; /* size of received file */
    /* continue receiving until ? (data or close) */
    while ( (rcvd_bytes = recv(sock, recv_str, MAX_RECV_BUF, 0)) > 0 )
    {
        recv_count++;
        rcvd_file_size += rcvd_bytes;
        if (write(f, recv_str, rcvd_bytes) < 0 )
        {
            perror("error writing to file");
            return -1;
        }
    }
    close(f); /* close file*/
    printf("Client Received: %d bytes in %d recv(s)\n", rcvd_file_size,
    recv_count);
    return rcvd_file_size;
}

//Code for deleting the file to server
int send_file_name_for_deletion(int sockfd, char* file_name)
{
    char send_str [MAX_SEND_BUF]; /* message to be sent to server*/
    int f; /* file handle for receiving file*/
    ssize_t sent_bytes, rcvd_bytes, rcvd_file_size;
    int recv_count; /* count of recv() calls*/
    char recv_str[MAX_RECV_BUF]; /* buffer to hold received data */
    size_t send_strlen; /* length of transmitted string */
    sprintf(send_str, "%s\n", file_name); /* add CR/LF (new line) */
    send_strlen = strlen(send_str); /* length of message to be transmitted */

    if( (sent_bytes = send(sockfd, file_name, send_strlen, 0)) < 0 ) {
        perror("send error");
        return -1;
    }
}

//Code for renaming the file on server
int send_file_for_renaming(int sockfd, char* file_name)
{
    char send_str [MAX_SEND_BUF]; /* message to be sent to server*/
    int f; /* file handle for receiving file*/
    ssize_t sent_bytes, rcvd_bytes, rcvd_file_size;
    int recv_count; /* count of recv() calls*/
    char recv_str[MAX_RECV_BUF]; /* buffer to hold received data */
    size_t send_strlen; /* length of transmitted string */
    sprintf(send_str, "%s\n", file_name); /* add CR/LF (new line) */
    send_strlen = strlen(send_str); /* length of message to be transmitted */

    if( (sent_bytes = send(sockfd, file_name, send_strlen, 0)) < 0 ) {
        perror("send error");
        return -1;
    }
}

int create_socket(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];

    printf("Reached create_socket function \n");

    if (argc < 3)
    {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);

    //create a socket for connection
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd  <0 )
    {
        error("Error opening socket");
    }
    else
    {
        printf("Socket created successfully !\n");
    }

    server = gethostbyname(argv[1]);

    if(server==NULL)
    {
        fprintf(stderr,"Error, no such host \n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);

    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0)
    {
        error("ERROR connecting");
    }
    else
    {
        printf("Connected to server\n");
    }
    return(sockfd);
}

int options(int argc, char *argv[])
{
    int option;
    int sockfd;
    option = 0;
    char* file_name = malloc(sizeof(char) * 128);;
    char buffer[256];

    while(option != 5)
    {
        printf("The available actions are - \n1. Upload File \n2. Download File \n3. Rename File \n4. Delete File \n5. Exit\n");
        printf("Please enter your action - ");
        scanf("%d", &option);

        if(option == 1)
        {
            //get a file name
            printf("Please enter a file name to be uploaded to the server : ");
            scanf("%s",file_name);
            printf("File to be uploaded to the server is : %s\n",file_name);
            //call the upload file
            printf("Calling socket function from upload function\n");
            sockfd = create_socket(argc, argv);
            printf("The socket received is : %d\n",sockfd);
            printf("Calling the upload function\n");
            send_action_to_server(sockfd,"upload");
            recv(sockfd, buffer, 255, 0);
            printf("%s\n",buffer);
            sockfd = create_socket(argc, argv);
            send_file(sockfd,file_name);
            close(sockfd);
        }
        if(option == 2)
        {
            //get a file name
            printf("Please enter a file name to be downloaded from the server : ");
            scanf("%s",file_name);
            printf("File to be downloaded from the server is : %s\n",file_name);
            //call the upload file
            printf("Calling socket function from download function\n");
            sockfd = create_socket(argc, argv);
            printf("The socket received is : %d\n",sockfd);
            printf("Calling the download function\n");
            send_action_to_server(sockfd,"download");
            recv(sockfd, buffer, 255, 0);
            printf("%s\n",buffer);
            sockfd = create_socket(argc, argv);
            recv_file(sockfd,file_name);
            close(sockfd);
        }
        if(option == 3)
        {
           //get a file name
            printf("Please enter a file name to be renamed on the server and the new name in the format <old name>-<new name> : ");
            scanf("%s",file_name);
            printf("File to be renamed and new name on the server is : %s\n",file_name);
            //call the upload file
            printf("Calling socket function from rename function\n");
            sockfd = create_socket(argc, argv);
            printf("The socket received is : %d\n",sockfd);
            printf("Calling the rename function\n");
            send_action_to_server(sockfd,"rename");
            recv(sockfd, buffer, 255, 0);
            printf("%s\n",buffer);
            sockfd = create_socket(argc, argv);
            send_file_for_renaming(sockfd,file_name);
            close(sockfd);
        }
        if(option == 4)
        {
            //get a file name
            printf("Please enter a file name to be deleted from the server : ");
            scanf("%s",file_name);
            printf("File to be deleted from the server is : %s\n",file_name);
            //call the upload file
            printf("Calling socket function from delete function\n");
            sockfd = create_socket(argc, argv);
            printf("The socket received is : %d\n",sockfd);
            printf("Calling the delete function\n");
            send_action_to_server(sockfd,"delete");
            recv(sockfd, buffer, 255, 0);
            printf("%s\n",buffer);
            sockfd = create_socket(argc, argv);
            recv_file(sockfd,file_name);
            close(sockfd);
        }
    }
}

int main(int argc, char *argv[])
{
    int option;
    option = options(argc, argv);
    return 0;
}
