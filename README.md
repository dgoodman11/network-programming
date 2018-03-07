# network-programming
Demonstration of network programming utilizing sockets API

This project has only 2 files: chatclient.c and chatserv.py. Below are the steps I took to successfully run the program.

1) Open two PuTTY windows, both using flip1.engr.oregonstate.edu

2) On one window, start the server program using the command:
	chatserv.py [PORTNUM]  
   I used port number 65501 for testing

3) In the other window, compile the client program using this command:
	g++ -o chatclient chatclient.c

4) Start the client program with the following command:
	client [SERVER_NAME] [SERVER_PORT_NUMBER]
   For testing, I used the server name 'localhost' and the port number 65501

5) The client and server should now be connected, and the client window will prompt you for the user's handle. Enter the handle you wish to use and press Enter.

6) The client will next prompt you to send a message. Enter the message you want to send to the server and press Enter.

7) Alternate sending messages between the server and client, and send the message "\quit" in either window when you're finished. This will cause the client to disconnect, and the server will continue listening for new connections. Restart the client program using instruction number (4) to start a new connection to the server.




