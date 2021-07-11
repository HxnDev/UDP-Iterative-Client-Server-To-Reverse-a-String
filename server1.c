// server program for udp connection 
#include <stdio.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include<netinet/in.h> 
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
	char *message; 
	int listenfd, len; 
	struct sockaddr_in servaddr, cliaddr; 
	bzero(&servaddr, sizeof(servaddr)); 

	// Create a UDP Socket 
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);		 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_family = AF_INET; 

	// bind server address to socket descriptor 
	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
	
	while(1)
	{
		//receive the datagram 
		len = sizeof(cliaddr); 
		int n = recvfrom(listenfd, buffer, sizeof(buffer), 
			0, (struct sockaddr*)&cliaddr,&len); //receive message from server 
		buffer[n] = '\0'; 
		puts(buffer); 
	
		message = rev(buffer);
		
		printf("Client's IP Number on Server's Side = %s", inet_ntoa(cliaddr.sin_addr));
		printf("Client's Port Number on Server's Side = %d", (int)ntohs(cliaddr.sin_port));
	
		// send the response 
		sendto(listenfd, message, MAXLINE, 0, 
		(struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
	}
} 
