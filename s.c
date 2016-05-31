#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>

#include <string.h>
#define NUM 256
#define USER admin
#define PASSWORD 1234 

int main( int argc, char *argv[] ) {
	int sockfd, newsockfd, portno, clilen;
	char buffer[NUM];
	char IP[NUM];
	char UserName[NUM];
	char Password[NUM];
	char  IPs [50][NUM];
	int WrongEntries [50];
	struct sockaddr_in serv_addr, cli_addr;
	int  n,pid;
   
	/* First call to socket() function */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("ERROR opening socket");
		exit(1);
	   }
   
   /* Initialize socket structure */
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = 5002;
   
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
   
   /* Now bind the host address using bind() call.*/
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR on binding");
		exit(1);
	}
      
   /* Now start listening for the clients, here process will
      * go in sleep mode and will wait for the incoming connection
   */
   
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
   
   /* Accept actual connection from the client */
	
	while (1) {
		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	
		if (newsockfd < 0) {
			perror("ERROR on accept");
			exit(1);
		}
	   	pid = fork();
		if (pid < 0) {
			perror("ERROR on fork");
			exit(1);
		}

		if (pid == 0) {
			bzero(buffer,256);
			n = read( newsockfd,buffer,255 );
		   
			if (n < 0) {
				perror("ERROR reading from socket");
				exit(1);
			}
		   
			printf("IP: %s\n",buffer);
			strncpy(IP, buffer, sizeof(buffer));
			bzero(buffer,256);
			n = read( newsockfd,buffer,255 );
			if (n < 0) {
				perror("ERROR reading from socket");
				exit(1);
			}
			strncpy(UserName, buffer, sizeof(UserName));
			printf("USER: %s\n",buffer);
			strncpy(UserName, buffer, sizeof(buffer));
			bzero(buffer,256);
			n = read( newsockfd,buffer,255 );
			if (n < 0) {
				perror("ERROR reading from socket");
				exit(1);
			}
			strncpy(Password, buffer, sizeof(Password));
			printf("PASSWORD: %s\n",buffer);
			strncpy(Password, buffer, sizeof(buffer));
		   /* Write a response to the client */

			n = write(newsockfd,"You Loged in.",18);
			if (n < 0) {
				perror("ERROR writing to socket");
				exit(1);
			}
		
		}
	   /* If connection is established then start communicating */

	}
		return 0;	
}  
   
