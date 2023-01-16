#include <Servo.h>

#define DISK_PIN 9
#define TOLKATEL_PIN 10
#define BQ_BLUETOOTH 19200
#define DEFAULT_DELAY 500
#define PISTON_DELAY 4000

Servo disk;
Servo tolk;

void checkData(char data);
void to_start(Servo serv);
void to_container_N1();
void to_container_N2();
void tolkatel();

void setup() 
{
  Serial.begin(BQ_BLUETOOTH);
  
  pinMode(DISK_PIN, OUTPUT);
  pinMode(TOLKATEL_PIN, OUTPUT);

  disk.attach(DISK_PIN);
  tolk.attach(TOLKATEL_PIN);
  
  to_start(disk);
  to_start(tolk);
}

void loop() 
{
 if (Serial.available() > 0) { 
    char dataBuffer = Serial.read();
    checkData(dataBuffer);
  }
}

void checkData(char data)
{  
    switch(data){
      case '1': 
      to_container_N1();
      break;
      
      case '2': 
      to_container_N2();
      break;

      case '0': 
      to_start(disk);
      break;
      
      default: 
      Serial.print("ERROR");
        }
  }

void to_start(Servo serv)
{
  serv.write(90);
  delay(DEFAULT_DELAY);
}

void to_container_N1() 
{
  disk.write(180);
  delay(DEFAULT_DELAY);
  tolkatel();
  to_start(disk);
}

void to_container_N2()
{
   disk.write(0);
   delay(DEFAULT_DELAY);
   tolkatel();
   to_start(disk);
}

void tolkatel()
{
  tolk.write(0);
  delay(DEFAULT_DELAY);
  to_start(tolk);
}
