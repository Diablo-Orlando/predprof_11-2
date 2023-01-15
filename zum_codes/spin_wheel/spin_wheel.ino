#include <Servo.h>

#define MOTOR_PORT 9
#define BQ_BLUETOOTH 19200
#define PISTON_DELAY 4

Servo serv;

void to_start();
void to_container_N1();
void to_container_N2();
void checkData(char data);

void setup() {
  pinMode(MOTOR_PORT, OUTPUT);
  serv.attach(MOTOR_PORT);
  Serial.begin(BQ_BLUETOOTH);
  
  to_start();
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
      to_start();
      break;
      
      default: 
      Serial.print("ERROR");
        }
  }

void to_start()
{
  serv.write(90);
  delay(500);
}

void to_container_N1() 
{
  serv.write(180);
  delay(500);
  //delay(PISTON_DELAY*1000);
  to_start();
}

void to_container_N2()
{
   serv.write(0);
   delay(500);
   //delay(PISTON_DELAY*1000);
   to_start();
}
