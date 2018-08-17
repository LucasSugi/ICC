/*
File: base.cpp

Kelvin Guilherme de Oliveira - 9293286
Lucas Yudi Sugi - 9293251
Mauricio Caetano da Silva - 9040996
*/

#include <string.h>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <strings.h>
#include <pthread.h>

using namespace std;

//This function will show the error that occurs when you try to connect
void error(string str){
	cerr << str << endl;
	exit(EXIT_FAILURE);
}


//Global variavable used to control the system monitor
bool speed = false;
bool temp = false;
bool autonomy = false;
bool human = false;

//Function will show sensors data 
void *monitorData(void *sck){

	int *sock;
	char buffer[150]; 
	string message, sensorName, valueMsg;
	size_t pos;

	//get socket
	sock = (int *) sck;

	while(true){
		recv(*sock, &buffer, 150, 0);
		message = buffer;

		//we used 'pos' to separete the message	
		pos = message.find(" ");

		//here we have the original message separete in type and value
		sensorName = message.substr(0,pos);
		valueMsg = message.substr(pos+1);

		//verify what the user wants to see	
		if(speed == true){
			if(sensorName.compare("Speed") == 0) 
				cout << sensorName << " " << valueMsg << "\n";
		}
		else if(temp == true){
			if(sensorName.compare("Temperature") == 0 )
				cout << sensorName << " " << valueMsg << "\n";
		}
		else if(autonomy == true){
			if(sensorName.compare("Autonomy") == 0 )
				cout << sensorName << " " << valueMsg << "\n";
		}
		else if(human == true){
			if(sensorName.compare("Health") == 0 ){
				cout << valueMsg << "\n";
			}
		}
	}
	return NULL;
}

//This function will show and control the menu 
void *showMenu(void *sck){

	//Initialize system
	printf("Loading system...\n");
	sleep(2);
	system("clear");

	int num, *sock;
	char *buffer;

	//get socket
	sock = (int*) sck;

	//create buffer
	buffer = (char*) malloc(sizeof(char) * 21);	

	//User menu
	while(true){
		printf("COMMAND MENU\n1 - Speed\n2 - Temperature\n3 - Autonomy\n4 - Health\n5 - Exit\nDigit: ");
		scanf("%s",buffer);
		num = atoi(buffer);

		//when one option is accept, we change the globlal variavable bool, to perform the monitor data	
		switch(num){
			case 1:
				system("clear");
				if(speed == false) printf("Speed(KM/H) - Any button to exit\n");
				speed = !speed;
				scanf("%s",buffer);
				speed = !speed;
				system("clear");
				break;
			case 2:
				system("clear");
				if(temp == false) printf("Temperature(Celsius) - Any button to exit\n");
				temp = !temp;
				scanf("%s",buffer);
				temp = !temp;
				system("clear");
				break;
			case 3:
				system("clear");
				if(autonomy == false) printf("Autonomy(KM) - Any button to exit\n");
				autonomy = !autonomy;
				scanf("%s",buffer);
				autonomy = !autonomy;
				system("clear");
				break;
			case 4:
				system("clear");
				if(human == false) printf("Health - Any button to exit\n");
				human = !human;
				scanf("%s",buffer);
				human = !human;
				system("clear");
				break;
			case 5:
				printf("Ending connection...\n");
				free(buffer);
				close(*sock);
				exit(EXIT_SUCCESS);
			default:
				break;
		}
	}
	return NULL;
}

int main (int argc, char* argv[]){
	//wait manager init
	sleep(3);

	//Port Number and file descriptor
	int listenFd, portNumber;

	//Structures from library <netinet/in.h> used to handling internet addresses
	struct sockaddr_in serverAddress;

	//This data type is used to represent an entry in the hosts database.
	struct hostent *server;

	if(argc < 3) error("Syntax : ./client <host name> <port>");

	portNumber = atoi(argv[2]);

	if((portNumber > 65535) || (portNumber < 2000)) error("Please enter port number between 2000 - 65535");

	//returns a file descriptor that can be used in later function calls that operate on sockets
	listenFd = socket(AF_INET, SOCK_STREAM, 0);

	if(listenFd < 0) error("Cannot open socket");

	//The gethostbyname() function returns a structure of type hostent for the given host name.
	server = gethostbyname(argv[1]);

	if(server == NULL) error("Host with this name does not exist");


	//This function sets all buffer values to zero. 
	//It takes two arguments, the first is a pointer to the buffer and the second is the size of the buffer.
	bzero((char *) &serverAddress, sizeof(serverAddress));

	//Defining the address family used in the communication domain
	serverAddress.sin_family = AF_INET;

	//The bcopy() function copies n bytes from src to dest.  The result is correct, even when both areas overlap.
	bcopy((char *) server -> h_addr, (char *) &serverAddress.sin_addr.s_addr, server -> h_length);


	//The htons() function makes sure that numbers are stored in memory in network byte order, 
	//which is with the most significant byte first. 
	serverAddress.sin_port = htons(portNumber);

	//The connect() function shall attempt to make a connection on a socket
	int checker = connect(listenFd,(struct sockaddr *) &serverAddress, sizeof(serverAddress));

	if (checker < 0) error("Cannot connect!");

	//send first mensage indicating he is a manager
	char buffer[5] = "base";
	send(listenFd,buffer,5,0);

	//Threads who will controll menu and data received
	pthread_t t1,t2;
	pthread_create(&t1,NULL,monitorData,&listenFd);
	pthread_create(&t2,NULL,showMenu,&listenFd);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
}
