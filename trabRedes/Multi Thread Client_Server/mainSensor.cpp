/*
File: mainSensor.cpp
Kelvin Guilherme de Oliveira - 9293286
Lucas Yudi Sugi - 9293251
Mauricio Caetano da Silva - 9040996
SERVER.CPP
*/

#include <time.h>
#include <ctime>
#include <fstream>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <pthread.h>
#include <sstream>

using namespace std;

#define MAX_THREADS 11
#define MAX_CONNECTIONS 10

#define TIME1 2
#define TIME2 3
#define TIME3 4
#define TIME4 5
//More information about this value: see in manual
#define CONSUMPTION 7.7057

//Struct used to pass information througth thread
typedef struct info{
	int sockCli;
	char *type;
	int time1,time2,time3,time4;
} INFO;


//Struct used to keep the value of sensors
typedef struct data{
	//Speed
	double wind, sPropellerL, sPropellerR;
	//Temperature
	double tPropellerL, tPropellerR, tElectricCentral;
	//Autonomy
	double fuel;
	//human
	double breathRate,heartbeat,bodyTemperature;
} DATA;

//create
DATA *data = (DATA*) malloc(sizeof(DATA));


/*
   Function used to handle with erros
   */
void error(string str){
	cerr << str << endl;
	exit(EXIT_FAILURE);
}

/*
   Function will save data received from sensors in a text file
   */
void saveLogFile(string message, int type){
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);
	int day, month, year, hour, min, sec;
	ofstream outputFile;

	day = aTime->tm_mday;
	month = aTime->tm_mon + 1; // Month is 0 – 11, add 1 to get a jan-dec 1-12 concept
	year = aTime->tm_year + 1900; // Year is # years since 1900
	hour = aTime->tm_hour;
	min = aTime->tm_min;
	sec = aTime->tm_sec;

	//Log of speed sensors
	if(type == 1){
		outputFile.open("SpeedSensorLog.txt", fstream::out | fstream::app);
		outputFile <<message<<" "<<"DATA: "<<day<<"/"<<month<<"/"<<year<<" - "<<hour<<":"<<min<<":"<<sec<<"\n";
	}
	//Log of temperature sensors
	else if(type == 2){
		outputFile.open("TempSensorLog.txt", fstream::out | fstream::app);
		outputFile <<message<<" "<<"DATA: "<<day<<"/"<<month<<"/"<<year<<" - "<<hour<<":"<<min<<":"<<sec<<"\n";
	}
	//Log of fuel sensor
	else if(type == 3){
		outputFile.open("FuelSensorLog.txt", fstream::out | fstream::app);
		outputFile <<message<<" "<<"DATA: "<<day<<"/"<<month<<"/"<<year<<" - "<<hour<<":"<<min<<":"<<sec<<"\n";
	}
	//Log of human sensor
	else if(type == 4){
		outputFile.open("HealthSensorLog.txt", fstream::out | fstream::app);
		outputFile <<message<<" "<<"DATA: "<<day<<"/"<<month<<"/"<<year<<" - "<<hour<<":"<<min<<":"<<sec<<"\n";
	}
	//Log of ....
	message.clear();
	outputFile.close();
}

/*
   Function that recieve data from sensors
   */
void *monitorSensor (void *fileDescriptor){
	ostringstream logTemp;
	string log;
	double buffer;
	bool run;

	INFO *info = (INFO*) fileDescriptor;

	run = true;
	while(run){
		recv(info->sockCli, &buffer, sizeof(double), 0);

		//store data in the right place
		if(strcmp(info->type,"wind") == 0){
			data->wind = buffer;	
			logTemp << "wind " << data->wind << "\0";
			log = logTemp.str();

			saveLogFile(log, 1);
		}
		else if( strcmp(info->type,"sPropellerL") == 0){	
			data->sPropellerL = buffer;
			logTemp << "sPropellerL " << data->sPropellerL << "\0";			
			log = logTemp.str();

			saveLogFile(log, 1);
		}
		else if( strcmp(info->type,"sPropellerR") == 0){
			data->sPropellerR = buffer;
			logTemp << "sPropellerR " << data->sPropellerR << "\0";			
			log = logTemp.str();

			saveLogFile(log, 1);
		}
		else if( strcmp(info->type,"tPropellerL") == 0){
			data->tPropellerL = buffer;
			logTemp << "tPropellerL " << data->tPropellerL << "\0";
			log = logTemp.str();

			saveLogFile(log, 2);
		}
		else if( strcmp(info->type,"tPropellerR") == 0){
			data->tPropellerR = buffer;
			logTemp << "tPropellerR " << data->tPropellerR << "\0";			
			log = logTemp.str();

			saveLogFile(log, 2);
		}
		else if( strcmp(info->type,"tElectricCentral") == 0){
			data->tElectricCentral = buffer;
			logTemp << "tEletricCentral " << data->tElectricCentral << "\0";			
			log = logTemp.str();

			saveLogFile(log, 2);
		}
		else if( strcmp(info->type,"fuel") == 0){
			data->fuel = buffer;
			logTemp << "fuel " << data->fuel << "\0";
			log = logTemp.str();

			saveLogFile(log, 3);
		}
		else if( strcmp(info->type,"breathRate") == 0){
			data->breathRate = buffer;
			logTemp << "breathRate " << data->breathRate << "\0";
			log = logTemp.str();

			saveLogFile(log, 4);
		}
		else if( strcmp(info->type,"heartbeat") == 0){
			data->heartbeat = buffer;
			logTemp << "heartbeat " << data->heartbeat << "\0";
			log = logTemp.str();

			saveLogFile(log, 4);
		}
		else if( strcmp(info->type,"bodyTemperature") == 0){
			data->bodyTemperature = buffer;
			logTemp << "bodyTemperature " << data->bodyTemperature << "\0";
			log = logTemp.str();

			saveLogFile(log, 4);
		}
		logTemp.str("");
		log.clear();
	}
	return NULL;
}	

/*
   This function is used for build the message with type and value to send for base
   */
string virtualSensors(int option){
	ostringstream msgTemp;
	string message = "";
	double speed, temp, autonomy;

	//Verify the type and built message
	if(option == 1){
		speed = (data->sPropellerL + data->sPropellerR)/2.0 - (0.23*data->wind);
		msgTemp << "Speed " << speed << "\0";
	}
	else if(option == 2){
		temp = (data->tPropellerL + data->tPropellerR + data->tElectricCentral)/3.0;
		msgTemp << "Temperature " << temp << "\0";
	}
	else if(option == 3){
		autonomy = (data->fuel * CONSUMPTION) - (0.12*data->wind) - (0.06* (data->sPropellerL + data->sPropellerR));
		msgTemp << "Autonomy " << autonomy << "\0";
	}
	else if(option == 4){
		//Here we check if person is weakened
		if(data->breathRate >= 20 || data->heartbeat >= 110 || data->bodyTemperature >= 38){
			msgTemp << "Health The person is not doing well";
			if(data->breathRate >= 20){
				msgTemp << " - BreathRate is high";
			}
			if(data->heartbeat >= 110){
				msgTemp << " - Heartbeat is high";
			}
			if(data->bodyTemperature >= 38){
				msgTemp << " - Body Temperature is high";
			}
			msgTemp << '\0';
		}
		else{
			msgTemp << "Health The person is doing well" << '\0';
		}
	}

	message = msgTemp.str();
	return message;
}

/*
   Function controls the communication between the airplane and the ground station
   */
void *chatWithBase(void *value){
	//wait to receive first values
	sleep(3);

	string message;
	char msg[150];

	INFO *info = (INFO*) value;

	//Here we have a different time for each sensor to send data	
	while(true){
		sleep(1);
		info->time1--;
		info->time2--;
		info->time3--;
		info->time4--;

		//Speed
		if(info->time1 < 0){
			message = virtualSensors(1);
			info->time1 = TIME1;
		}

		//Temperature
		else if(info->time2 < 0){
			message = virtualSensors(2);
			info->time2 = TIME2;
		}

		//Autonomy
		else if(info->time3 < 0){
			message = virtualSensors(3);
			info->time3 = TIME3;
		}

		//Health 
		else if(info->time4 < 0){
			message = virtualSensors(4);
			info->time4 = TIME4;
		}

		strcpy(msg, message.c_str());
		send(info->sockCli, &msg, message.size()+1, 0);
		message.clear();
	}
	return NULL;
}


/*
   This function perform the conection with sensors
   */
void listenConnections(int listenFd){   
	int connFd;	

	//Structures from library <netinet/in.h> used to handling internet addresses
	struct sockaddr_in clientAddress;

	//socklen_t: unsigned integral type of length of at least 32 bits
	//It stores the size of the address
	socklen_t len;

	int numberOfThreads = 0;

	//it's used to identify a thread.
	pthread_t threadA[MAX_THREADS];

	INFO **info = (INFO**) malloc(sizeof(INFO*) * (MAX_THREADS));

	//The while condition is just a test
	while (numberOfThreads < MAX_THREADS){
		len = sizeof(clientAddress);
		//Here is where client connects. Server will hang in this mode until client connect
		connFd = accept(listenFd, (struct sockaddr *)&clientAddress, &len);

		if (connFd < 0)
			error("Cannot accept connection");

		//struct with information about socket
		info[numberOfThreads] = (INFO*) malloc(sizeof(INFO));
		info[numberOfThreads]->sockCli = connFd;

		//verify what is the client
		char buffer[20];
		bzero(buffer,20);
		recv(connFd,buffer,20,0);

		//copy type of client
		info[numberOfThreads]->type = (char*) calloc(sizeof(char),( strlen(buffer)+1));
		strcpy(info[numberOfThreads]->type,buffer);

		numberOfThreads++;
	}

	//Verify if client is a sensor or a base
	for(int i=0;i<numberOfThreads;i++){
		if(strcmp(info[i]->type,"base") == 0) {
			info[i]->time1 = TIME1;
			info[i]->time2 = TIME2;
			info[i]->time3 = TIME3;
			info[i]->time4 = TIME4;
			pthread_create(&threadA[i], NULL, chatWithBase, (void*)info[i]);
		}
		else pthread_create(&threadA[i], NULL, monitorSensor, (void*)info[i]); 
	}

	//run threads after end program 
	for(int i=0;i<numberOfThreads;i++){
		pthread_join(threadA[i],NULL);	
	}

	free(info);
}

int main(int argc, char* argv[]){
	//Structures from library <netinet/in.h> used to handling internet addresses
	struct sockaddr_in serverAddress;

	//PortNumber and file descriptor
	int portNumber, listenFd;

	if (argc < 2) error("Syntam : ./server <port>"); 

	portNumber = atoi(argv[1]);

	//In TCP and UDP protocols, the gates have 16 bits, so the max possible value is 65535
	if((portNumber > 65535) || (portNumber < 2000)) error("Please enter a port number between 2000 - 65535");

	// Returns a file descriptor that can be used in later function calls that operate on sockets
	listenFd = socket(AF_INET, SOCK_STREAM, 0);

	if(listenFd < 0) error("Cannot open socket");

	//This function sets all buffer values to zero. 
	bzero((char*) &serverAddress, sizeof(serverAddress));

	//Defining the arguments that describes the socket
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(portNumber);

	//The bind() system call binds a socket to an address, in this case the address of the 
	//current host and port number on which the server will run.
	if( bind(listenFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) error("Cannot bind");

	//Listen for socket connections and limit the queue of incoming connections
	listen(listenFd, MAX_CONNECTIONS);	

	//Wait for connections
	listenConnections(listenFd);	
}
