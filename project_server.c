/*
Soham Joshi 1641055 
Jay Patel 1641064
To achieve File transfer using TCP/IP Protocol
*/


#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/* error function */
void error(const char *message)
{
    perror(message);
    exit(1);
}

int main(int argc, char *argv[])
{
     int socket_FD, newsocket_FD, port_num;

     socklen_t client_length;

     char buff[512];

     struct sockaddr_in serv_addr, cli_addr;
     int n;

     if (argc < 2)
	 {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

	//Socket function will create unbound socket and return file descriptor that can be used in later function calls
     socket_FD = socket(AF_INET, SOCK_STREAM, 0);

	//If the socket is not created properly, display the error
     if (socket_FD < 0) 
	{
        error("ERROR!! in opening the socket");
	}
	// bzero() function copies n bytes, each with a value of zero, into string s
     bzero((char *) &serv_addr, sizeof(serv_addr));
	//atoi will convert a string into an integer numerical representation.
     port_num = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(port_num);

		//Binding....
     if (bind(socket_FD, (struct sockaddr *) &serv_addr,
     sizeof(serv_addr)) < 0) 
     error("ERROR on binding.....");

	//Listen....
     listen(socket_FD,5);
     client_length = sizeof(cli_addr);

		//accept...
     newsocket_FD = accept(socket_FD, 
                 (struct sockaddr *) &cli_addr, 
                 &client_length);


     if (newsocket_FD < 0) 
         error("ERROR on ACCEPT........");
          
      
        //wriring into file file_recieved  
        FILE *fp;
        int words, ch = 0;
        fp = fopen("file_received.txt","a");            
      
		read(newsocket_FD, &words, sizeof(int));
            
         while(ch != words)
       	   {
        	read(newsocket_FD , buff , 512); 
	   		fprintf(fp , " %s" , buff);   
			ch++;
	   }

       printf("The file was received successfully\n");
	   printf("The new file which is created is file_recieved.txt");

     close(newsocket_FD);
     close(socket_FD);

     return 0; 
}
