/* A simple server in the internet domain using TCP the port number is passed as an argument */

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

int MAX_RECV_BUF = 256;
int MAX_SEND_BUF = 256;

void error(char *msg)
{
    perror(msg);
    exit(1);
}

void get_action_name_from_client(int sock, char* action)
{
    char recv_str[MAX_RECV_BUF]; /* to store received string */
    ssize_t rcvd_bytes; /* bytes received from socket */
    printf("Reached in get_file_name function\n");

    /* read name of requested file from socket */
    if ( (rcvd_bytes = recv(sock, recv_str, MAX_RECV_BUF, 0)) < 0) {
        perror("recv error");
        return;
    }
    sscanf (recv_str, "%s\n", action); /* discard CR/LF */
    printf("Name of action is %s\n", recv_str);
}

void get_file_name_from_client(int sock, char* file_name)
{
    char recv_str[MAX_RECV_BUF]; /* to store received string */
    ssize_t rcvd_bytes; /* bytes received from socket */
    printf("Reached in get_file_name function\n");

    /* read name of requested file from socket */
    if ( (rcvd_bytes = recv(sock, recv_str, MAX_RECV_BUF, 0)) < 0) {
        perror("recv error");
        return;
    }
    sscanf (recv_str, "%s\n", file_name); /* discard CR/LF */
    printf("Name of received file is %s\n", recv_str);
}

int send_file_to_client(int sock, char *file_name)
{
    int sent_count; /* how many sending chunks, for debugging */
    ssize_t read_bytes, /* bytes read from local file */
    sent_bytes, /* bytes sent to connected socket */
    sent_file_size;
    char send_buf[MAX_SEND_BUF]; /* max chunk size for sending file */
    char * errmsg_notfound = "File not found\n";
    int f; /* file handle for reading local file*/
    sent_count = 0;
    sent_file_size = 0;

    /* attempt to open requested file for reading */
    if( (f = open(file_name, O_RDONLY)) < 0) /* can't open requested file */
    {
        perror(file_name);
        if( (sent_bytes = send(sock, errmsg_notfound ,strlen(errmsg_notfound), 0)) < 0 )
        {
        perror("send error");
        return -1;
        }
    }
    else /* open file successful */
    {
        printf("Sending file: %s\n", file_name);
        while( (read_bytes = read(f, send_buf, MAX_RECV_BUF)) > 0 )
        {
        if( (sent_bytes = send(sock, send_buf, read_bytes, 0))
        < read_bytes )
        {
        perror("send error");
        return -1;
        }
        sent_count++;
        sent_file_size += sent_bytes;
        }
        close(f);
    } /* end else */

    printf("Done with this client. Sent %d bytes in %d send(s)\n\n",sent_file_size, sent_count);
    return sent_count;
}

void get_file_from_client(int newsockfd,char *file_name)
{
   char buffer[256];
   bzero(buffer,256); // clear the buffer of any values
   int n;
   n = read(newsockfd,buffer,255); // this will read the information coming in on the socket to the buffer of max size 255

   if (n < 0)
   {
       error("ERROR reading from socket");
   }
   else
   {
        printf("Reading from socket now \n");
   }

   FILE *fp;

   fp = fopen(file_name,"w");

   while(n>0)
   {
        fputs(buffer, fp);
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
   }
   fclose(fp);
   printf("Data written to file\n");

}

void delete_file_from_server(int newsockfd,char *file_name)
{
    // Open the file that we wish to delete
    FILE *fp = fopen(file_name,"rb"); //take a sample file
    int ret;
    if(fp==NULL)
    {
        printf("File does not exist on the server\n");
        return 1;
    }
    else
    {
       fclose(fp);
       ret = remove(file_name);

       if(ret == 0)
       {
          printf("File deleted successfully\n");
       }
       else
       {
          printf("Error: unable to delete the file\n");
       }
    }
}

void rename_file_on_server(int newsockfd,char *file_name)
{
    //Tokenize the string to extract the file names for renaming
    char *token, *token1;
    char ch;
    const char s[2] = " ";
    int ret;
    FILE * intermediate;
    /* get the first token */
    token = strtok(file_name, "-");
    FILE * source = fopen(token,"rb");
    if(source == NULL)
    {
        printf("File does not exist on the server\n");
    }
    else
    {
        intermediate = fopen("intermediate.txt","a");
        while( ( ch = fgetc(source) ) != EOF )
        fputc(ch, intermediate);
        fclose(source);
        fclose(intermediate);
        ret = remove(token);
    }

    printf( "The current file name is %s\n", token);
    token = strtok(NULL,"-");
    printf("The file is to be renamed to %s\n", token);
    rename("intermediate.txt",token);
    printf("File renamed successfully\n");
}

int main(int argc, char *argv[])
{

    int sockfd, newsockfd, portno, clilen;

    struct sockaddr_in serv_addr, cli_addr;
    char file_name [MAX_RECV_BUF];
    char action[MAX_RECV_BUF];
    int n;
    size_t send_strlen;
    send_strlen = strlen("Received action, please send file name\n");

    if (argc < 2)  // checks for the number of characters being passed at the command line
    {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    else
    {
        printf("The argc value is %d\n", argc);
    }

    // gets a socket open
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        error("ERROR opening socket");

    }
    else
    {
        printf("Socket has been opened.... the sockfd value is %d\n",sockfd);
    }

    // clears the server addr struct of any values
    bzero((char *) &serv_addr, sizeof(serv_addr));

    // gets the first argument from argv and converts character array value into integer using atoi
    portno = atoi(argv[1]);

    // tells the server that it should expect an ip address type value
    serv_addr.sin_family = AF_INET;

    // tells the server that it should get any address
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    //converts the port number into a network understandable format
    serv_addr.sin_port = htons(portno);

    // we have the socket and server address... we need to bind them together using bind function
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
        error("ERROR on binding");
    }
    else
    {
        printf("Socket has been binded\n");
    }

    while(1)
    {

        listen(sockfd,1);
        clilen = sizeof(cli_addr);

        //create a new socket if an input request is received from the client
        newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

        if (newsockfd < 0)
        {
            error("ERROR on accept");
        }
        else
        {
            printf("New socket created after accept\n");
        }

        printf("Calling the get action name function\n");
        get_action_name_from_client(newsockfd, action);
        printf("The action received is %s\n",action);
        if(strcmp(action,"upload")==0)
        {
            printf("In upload\n");
            write(newsockfd,"Received action, please send file name\n",send_strlen);
            listen(sockfd,5);
            newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

            printf("Calling the get_file_name function\n");
            get_file_name_from_client(newsockfd, file_name);

            printf("Calling the get_file_from_client function\n");
            get_file_from_client(newsockfd, file_name);

            close(newsockfd);
        }

        if(strcmp(action,"download")==0)
        {
            printf("In download\n");
            write(newsockfd,"Received action, please send file name\n",send_strlen);
            listen(sockfd,5);
            newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

            printf("Calling the get_file_name function\n");
            get_file_name_from_client(newsockfd, file_name);

            printf("Calling the send_file_to_client function\n");
            send_file_to_client(newsockfd, file_name);

            close(newsockfd);
        }

        if(strcmp(action,"delete")==0)
        {
            printf("In delete\n");
            write(newsockfd,"Received action, please send file name\n",send_strlen);
            listen(sockfd,5);
            newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

            printf("Calling the get_file_name function\n");
            get_file_name_from_client(newsockfd, file_name);

            printf("Calling the delete_file_from_server function\n");
            delete_file_from_server(newsockfd, file_name);

            close(newsockfd);
        }

        if(strcmp(action,"rename")==0)
        {
            printf("In rename\n");
            write(newsockfd,"Received action, please send file name\n",send_strlen);
            listen(sockfd,5);
            newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

            printf("Calling the get_file_name function\n");
            get_file_name_from_client(newsockfd, file_name);

            printf("Calling the rename_file_on_server function\n");
            rename_file_on_server(newsockfd, file_name);

            close(newsockfd);
        }
        printf("End of all options.. we start again !\n");
    }
}
