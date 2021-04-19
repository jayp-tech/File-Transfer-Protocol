/*
Soham Joshi 1641055 
Jay Patel 1641064
To achieve File transfer using TCP/IP Protocol
*/

/*
	Client Side
	Pass ip address and port no as command line arguments in the same sequence
	Provide inputfile.txt before executing the programm
*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>


void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{

    int socket_FD, port_num, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[512];

    if (argc < 3)
    {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    port_num = atoi(argv[2]);


//Socket function will create unbound socket and return file descriptor that can be used in later function calls
    socket_FD = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_FD < 0) 
        error("ERROR in opening the socket");

    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }


	// bzero() function copies n bytes, each with a value of zero, into string s
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

	//bocpy() functin will copy n bytes from the area pointed to by s1 to the area pointed to by s2
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);

	//htons() will convert values between host and netowk byte orders
    serv_addr.sin_port = htons(port_num);
    if (connect(socket_FD,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
  
        bzero(buffer,512);
        
    FILE *f;
    
    int words = 0;
    char c;
	//Opening file in the read mode
     f=fopen("inputfile.txt","r");

	//Counting No of words in the file......
    while((c=getc(f))!=EOF)			
	{	
		fscanf(f , "%s" , buffer);
		if(isspace(c)||c=='\t')
		words++;	
	}
	
     
    //write() is used to write data out of a buffer 
	write(socket_FD, &words, sizeof(int));
//Rewind function sets the file position to the beginning of the file
    rewind(f);
      
          
    char ch ;
       while(ch != EOF)
      {
		
		fscanf(f , "%s" , buffer);
		write(socket_FD,buffer,512);
		ch = fgetc(f);
      }

	printf("The file has been sent successfully");
    
//Closing the socket...
    close(socket_FD);
    return 0;
}
