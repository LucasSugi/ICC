PORT=3124
./mainSensor $PORT  &
./sensor localhost $PORT wind 130.4 213.3 &
./sensor localhost $PORT sPropellerL 372.3 378.7 &
./sensor localhost $PORT sPropellerR 371.8 380.5 &
./sensor localhost $PORT tPropellerL 107.2 125.9 &
./sensor localhost $PORT tPropellerR 108.5 127.4 &
./sensor localhost $PORT tElectricCentral 86.1 117.2 &
./sensor localhost $PORT fuel 190 190 &
./sensor localhost $PORT breathRate 12 20 &
./sensor localhost $PORT heartbeat 60 110 &
./sensor localhost $PORT bodyTemperature 36.8 38 &
./base localhost $PORT 
