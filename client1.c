// udp client driver program 
#include <stdio.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include<netinet/in.h> 
#include<unistd.h> 
#include<stdlib.h> 

#define PORT 5000 
#define MAXLINE 1000 

char *rev(char *s)
{
	int size = strlen(s);
	char* out = malloc(size);
	int x = size-1; 	//Will reverse
	for (int i=0; i<size; i++)
	{
		out[x--] = s[i];
	}
	
	return out;

}


// Driver code 
int main() 
{ 
	char buffer[100]; 
	char message[30]; 
	int sockfd, n; 
	struct sockaddr_in servaddr; 
	
	// clear servaddr 
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_family = AF_INET; 
	
	// create datagram socket 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
	
	// connect to server 
	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
	{ 
		printf("\n Error : Connect Failed \n"); 
		exit(0); 
	}
	
	while(1)
	{
		printf("Enter the message for server = ");
		gets(message);
		printf("\n");
		// request to send datagram 
		// no need to specify server address in sendto 
		// connect stores the peers IP and port 
		sendto(sockfd, message, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr)); 
	
		// waiting for response 
		recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL); 
		puts(buffer);
		
		printf("Server's IP Number on Client's Side = %s", inet_ntoa(servaddr.sin_addr));
		printf("Server's Port Number on Client's Side = %d", (int)ntohs(servaddr.sin_port));
	} 
	// close the descriptor 
	close(sockfd); 
} 
