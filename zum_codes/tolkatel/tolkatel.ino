#include <Servo.h>

#define pin 10
#define SERIAL 9200

void start_work();

Servo serv;

void setup() 
{
  pinMode(pin, OUTPUT);
  serv.attach(pin);
  Serial.begin(SERIAL);

  
}

void loop() 
{
  bool ser_ready = Serial.read() > 0;
  if (ser_ready > 0)
    check_data();
}

void check_data() 
{
  char buff_char = Serial.read();
    switch(buff_char) {
      case '1': 
        start_work();
        break;
      default: Serial.print("ERROR");
      }
}

void start_work() 
{
  serv.write(0);
  delay(500);
  serv.write(90);
}
