/*
File: Sensor.cpp

Kelvin Guilherme de Oliveira - 9293286
Lucas Yudi Sugi - 9293251
Mauricio Caetano da Silva - 9040996
*/

#include <time.h>
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
using namespace std;

/*
   Function used to handle with erros
   */
void error(string str){
	cerr << str << endl;
	exit(EXIT_FAILURE);
}

/*
   Function used to send data to the central sensor 
   */
void sensor(char* sensorName, int listenFd, double minValue, double maxValue){
	int counterFuel = 0;
	double value;

	//Initial message who identifies which sensor is sending messages
	send(listenFd, sensorName, strlen(sensorName)+1, 0);

	value = minValue;

	srand((unsigned)time(NULL));
	while(true){
		//For different fuel sensors we have a random value calculation
		if( strcmp(sensorName,"fuel") != 0){
			value = minValue + (double)(rand() % (int)(maxValue - minValue));
		}
		//For fuel we have one fixed value, that will be decrease after 5 times
		else{
			if(counterFuel == 5){
				value--;	
				counterFuel = 0;
			}
		}	
		counterFuel++;
		send(listenFd, &value, sizeof(double), 0);
		sleep(4);
	}
}

/*
   Function used to send data to the central sensor 
   */
void humanSensor(char* sensorName, int listenFd, double minValue, double maxValue){
	int r;
	double value;

	//Initial message who identifies which sensor is sending messages
	send(listenFd, sensorName, strlen(sensorName)+1, 0);

	srand((unsigned)time(NULL) + minValue);
	while(true){
		//Here we have a 2% chance of the person being debilitated 
		r = rand() % 100;
		if(r >= 98){
			//If persorn is debilitated, this will be sustained
			while(true){
				if( strcmp(sensorName,"breathRate") == 0){
					value = maxValue + rand() % 10;
				}
				else if(strcmp(sensorName,"heartbeat") == 0){
					value = maxValue + rand() % 20;
				}
				else if(strcmp(sensorName,"bodyTemperature") == 0){
					value = maxValue + rand() % 7;
				}
				send(listenFd, &value, sizeof(double), 0);
				sleep(4);
			}
		}
		value = minValue + (double)(rand() % (int)(maxValue - minValue));
		send(listenFd, &value, sizeof(double), 0);
		sleep(4);
	}
}

int main (int argc, char* argv[]){
	//wait manager init
	sleep(3);

	//Port Number and file descriptor
	int listenFd, portNumber, minValue, maxValue;
	char *sensorName = (char*) calloc(40,sizeof(char));

	//Structures from library <netinet/in.h> used to handling internet addresses
	struct sockaddr_in serverAddress;

	//This data type is used to represent an entry in the hosts database.
	struct hostent *server;

	if(argc < 6)	error("Syntax : ./sensor <host name> <port> <sensor name> <min> <max>");

	portNumber = atoi(argv[2]);
	bcopy(argv[3], sensorName, strlen(argv[3])+1);
	minValue = atoi(argv[4]);
	maxValue = atoi(argv[5]);

	if((portNumber > 65535) || (portNumber < 2000))
		error("Please enter port number between 2000 - 65535");

	//returns a file descriptor that can be used in later function calls that operate on sockets
	listenFd = socket(AF_INET, SOCK_STREAM, 0);

	if(listenFd < 0) error("Cannot open socket");

	//The gethostbyname() function returns a structure of type hostent for the given host name.
	server = gethostbyname(argv[1]);
	if(server == NULL) error("Host with this name does not exist");


	//This function sets all buffer values to zero. 
	bzero((char *) &serverAddress, sizeof(serverAddress));

	//Defining the address family used in the communication domain
	serverAddress.sin_family = AF_INET;

	//The bcopy() function copies n bytes from src to dest.  The result is correct, even when both areas overlap.
	bcopy((char *)server->h_addr, (char *)&serverAddress.sin_addr.s_addr, server->h_length);


	//	The htons() function makes sure that numbers are stored in memory in network byte order, 
	//	which is with the most significant byte first
	serverAddress.sin_port = htons(portNumber);

	//	The connect() function shall attempt to make a connection on a socket
	int checker = connect(listenFd,(struct sockaddr *) &serverAddress, sizeof(serverAddress));

	if (checker < 0) error("Cannot connect!");

	//Human sensors is different of physical sensors
	if( strcmp(sensorName,"breathRate") == 0 || strcmp(sensorName,"heartbeat") == 0 || strcmp(sensorName,"bodyTemperature") == 0){
		humanSensor(sensorName,listenFd,minValue,maxValue);
	}
	else{
		sensor(sensorName, listenFd, minValue, maxValue); 
	}
	free(sensorName);
	return 0;
}
