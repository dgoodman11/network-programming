/*****************************************************************************
* Program Description: The client side of a chat app implemented in C. The 
*    user on this end takes turns sending messages to server side. This
*    program takes 2 arguments on the command line: the host name and port
*    number, in that order.
* Name: Danielle Goodman
* Date: 2/12/2018
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//header info for functions located below with function definitions
int setupConnection(int portNum, char *hostName);
int sendMessage(int socket, char *handle);
int receiveMessage(int socket);

int main(int argc, char *argv[]) {
   int quit1; //bool value - if the user inputs or client receives "\quit"
   int socket;
   char handle[11]; 

   //establish connection and return socket
   socket = setupConnection(atoi(argv[2]), argv[1]);
   
   //get user handle and prepare for appending it to sent messages
   memset(handle, '\0', sizeof(handle));
   printf("Please enter the user's handle\n");
   fgets(handle, sizeof(handle), stdin);
   handle[strlen(handle) - 1] = '\0';

   //enters infinite loop and continues exchanging messages with the
   //server until one of them enteres the command "\quit". The value
   //returned to the quit variable represents if the quit command
   //was entered or received
   while (1) {
      quit = sendMessage(socket, handle);
	if (quit) {
	   close(socket);
	   exit(0);
 	}
      quit = receiveMessage(socket); 
	if (quit) {
	   close(socket);
	   exit(0);
	}  
   }

  
   return 0;

}


/********************************************************************
* Description: this function receives a message from the server side
*    and returns the value "1" if the message received is "\quit" 
*    or prints the message to the screen if any other message is
*    received
* Inputs: and int that represents the socket connection
* Outputs: int value of 1 or 0 representing whether or not to quit
*    the chat based on the message received
********************************************************************/
int receiveMessage(int socket) {
   int quitChat = 0;
   char recvMessage[500];
   memset(recvMessage, '\0', sizeof(recvMessage));
   recv(socket, recvMessage, sizeof(recvMessage), 0);

   //is message "\quit"
   if (strcmp(recvMessage, "\\quit") == 0) {
	printf("QUITTING CHAT\n");
	quitChat = 1;
	return quitChat; //return here before message can be printed
   }

   printf("%s\n", recvMessage);

   return quitChat;

}

/*******************************************************************
* Description: This function sends a user-entered message to the 
*    server. It prompts the user to enter a message and checks
*    if the message is "\quit". If so, sets quitChat variable
*    to 1 and sends the message. Otherwise, appends the user 
*    handle to the message and sends to server
* Inputs: An int representing the socket connection and a pointer
*    to char that represents the user-entered handle. This handle
*    is appended to all sent messages 
* Outputs: An int used as bool value representing whether or not 
*   to quit the chat based on message entered by user
*******************************************************************/
int sendMessage(int socket, char *handle) {
   int quitChat = 0;
   char buffer[500];
   char displayMessage[515];
   memset(displayMessage, '\0', sizeof(buffer));
   
   //get message to send
   printf("%s> ", handle);
   memset(buffer, '\0', sizeof(buffer));
   fgets(buffer, sizeof(buffer), stdin);

   //check if entered message is command to quit
   if (strcmp(buffer, "\\quit\n") == 0) {
      printf("QUITTING CHAT\n");
      quitChat = 1;
      buffer[strlen(buffer) - 1] = '\0';
      send(socket, buffer, strlen(buffer), 0);
      return quitChat;
   }

   //append handle to message sent
   strcat(displayMessage, handle);
   strcat(displayMessage, "> ");
   strcat(displayMessage, buffer);
   displayMessage[strlen(displayMessage) - 1] = '\0';
   send(socket, displayMessage, strlen(displayMessage), 0);

   return quitChat;
}

/******************************************************************
* Description: This function sets up the connection with the 
*    server
* Inputs: An int representing the port number and and pointer to
*    char representing the host name of the server the program
*    will connect to. Both values are entered by the user when
*    the start the program
* Outputs: An int representing the socket connection that was 
*    established
******************************************************************/ 
int setupConnection(int portNumber, char *hostName) {

   int socketfd;
   struct sockaddr_in serverAddress;
   struct hostent *server;

   memset((char*)&serverAddress, '\0', sizeof(serverAddress));
   serverAddress.sin_family = AF_INET;
   serverAddress.sin_port = htons(portNumber);
   server = gethostbyname(hostName);
   memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)server->h_addr, server->h_length);

   socketfd = socket(AF_INET, SOCK_STREAM, 0);
   
   connect(socketfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

   printf("READY TO SEND TO SERVER\n");

   return socketfd;

}

