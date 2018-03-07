#!/usr/bin/python

################################################################################
# Program Description: The server side of a chat app. It takes one argument - the
#   port number to establish the connection on. The connection with the client 
#   continues until the server or the client sends the message "\quit". The server
#   stops listening only when the user enters Ctrl-C to send a SIGINT
# Name: Danielle Goodman
# Date: 2/12/2018
################################################################################

from socket import *
import sys


################################################################################
# Description: sets up a socket on a user-specified port number
# Inputs: the port number that will be bound to the socket
# Outputs: the created socket
################################################################################
def socketSetup(portNum):
	serverSocket = socket(AF_INET,SOCK_STREAM)
	serverSocket.bind(('', portNum)) 
	serverSocket.listen(1)
	return serverSocket

################################################################################
# Description: sends user-entered  message to client side once a link is established
# Inputs: an initialized socket
# Outputs: a bool value representing whether or not the message entered by the user
#   is "\quit"
################################################################################
def sendMessage(connectionSocket):
	quitChatting = 0
	userInput = raw_input()
	connectionSocket.send(userInput)
	if userInput == '\quit':
		quitChatting = 1
		print "QUITTING CHAT"
	return quitChatting

################################################################################
# Description: receives message from client and prints it to the screen. Monitors
#  for received message of "\quit"
# Inputs: an initialized socket
# Outputs: a bool value representing whether or not the message received from the 
#   client is "\quit"
################################################################################
def receiveMessage(connectionSocket):
	quitChatting = 0
	messageRecv = connectionSocket.recv(515)
	if messageRecv == '\quit':
		quitChatting = 1
		print "QUITTING CHAT"
	else:
		print messageRecv

	return quitChatting


#Set up socket, wait for connection, and enter chat
serverPort = int(sys.argv[1]) #the port number is the user-entered argument
serverSocket = socketSetup(serverPort)

while 1:
	print 'WAITING FOR CONNECTION'
	connectionSocket, addr = serverSocket.accept()
	print 'CONNECTION STARTED'

	while (1):
		clientQuit = receiveMessage(connectionSocket)
		if clientQuit: break
		serverQuit = sendMessage(connectionSocket)
		if serverQuit: break
		

	connectionSocket.close()

