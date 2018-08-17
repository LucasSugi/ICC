FLAGS =  -Wall -lpthread

all: mainSensor.o sensor.o base.o
	g++ mainSensor.o $(FLAGS) -o mainSensor
	g++ sensor.o $(FLAGS) -o sensor
	g++ base.o $(FLAGS) -o base

mainSensor.o: mainSensor.cpp
	g++ $(FLAGS) mainSensor.cpp -c

sensor.o: sensor.cpp
	g++ $(FLAGS) sensor.cpp -c

base.o: base.cpp
	g++ $(FLAGS) base.cpp -c
clean:
	rm -f *.o *.txt mainSensor sensor base
