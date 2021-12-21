// Define Softserials
#define NUM_COM 1
#define SERIAL_PARAM0 SERIAL_8N1
#define SERIAL0_RXPIN 21
#define SERIAL0_TXPIN 1

HardwareSerial* COM[NUM_COM] = {&Serial};

float startlat=5412.998;
float startlong=936.007;
float dmraddisth=20;
float dmraddistv=20;
float dmradbearing=-180;


int nmea0183_checksum(char *nmea_data)
{
    int crc = 0;
    int i;
    for (i = 1; i < strlen(nmea_data); i ++) {
        crc ^= nmea_data[i];
    }
    return crc;
}

void outputmessage(char *nmea_data)
{
    COM[0]->print(nmea_data);
    COM[0]->print("*");
    COM[0]->println(nmea0183_checksum(nmea_data),HEX);
}

void setup() {
  COM[0]->begin(19200, SERIAL_PARAM0, SERIAL0_RXPIN, SERIAL0_TXPIN); 
}

void loop()
{
  startlat=startlat-0.001;
  startlong=startlong-0.006;

  
  dmraddisth=dmraddisth-0.005;
  dmraddistv=dmraddistv-0.01;
  
  String opstring;
  
  opstring="$GPRMC,185726.800,A,";
  opstring+=String(startlat,3);
  opstring+=",N,00";
  opstring+=String(startlong,3);
  opstring+=",E,43,259,191221,0.0,E,A";
x
  outputmessage(&opstring[0]);
  delay(50);

  opstring="$PFLAU,2,1,2,1,1,-45,2,";
  opstring+=String(dmraddisth,0);
  opstring+=",";
  opstring+=String(dmraddistv,0);
  opstring+=",3FEBA7";
  outputmessage(&opstring[0]);

  delay(50);

    outputmessage("$PFLAA,0,-1234,1234,220,2,3FF648,180,,30,-1.4,1");

  delay(300);

  
}
