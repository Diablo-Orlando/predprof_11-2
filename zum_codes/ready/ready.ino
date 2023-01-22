#include <Servo.h>

#define DISK_PIN 3
#define TOLKATEL_PIN 10
#define s0 8
#define s1 9
#define s2 10
#define s3 11
#define sOut 12

#define BQ_BLUETOOTH 19200
#define DEFAULT_DELAY 500
#define PISTON_DELAY 4000

Servo disk;
Servo tolk;

void checkData();
void to_start(Servo serv);
void to_container_N1();
void to_container_N2();
void tolkatel();
void scan();
void checkColor(char c);

char color;
char container_1_colors[2] {};
char container_2_colors[2] {};

int redfrequency = 0;
int bluefrequency = 0;
int greenfrequency = 0;

int redColor = 0;
int greenColor = 0;
int blueColor = 0;

void setup() 
{
  Serial.begin(BQ_BLUETOOTH);

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);

  pinMode(sOut, INPUT);

  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
  
  pinMode(DISK_PIN, OUTPUT);
  pinMode(TOLKATEL_PIN, OUTPUT);

  disk.attach(DISK_PIN);
  tolk.attach(TOLKATEL_PIN);
  
  to_start(disk);
  to_start(tolk);
}

void loop() 
{
 if (Serial.available() >= 4) { 
    checkData();
  }
}

void checkData()
{  
   container_1_colors[0] = Serial.read();
   container_1_colors[1] = Serial.read();
   container_2_colors[0] = Serial.read();
   container_2_colors[1] = Serial.read();
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

void scan()
{
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  redfrequency = pulseIn(sOut, LOW);
  redColor = map(redfrequency, 8, 174, 255, 0);

  delay(100);
  
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  greenfrequency = pulseIn(sOut, LOW);
  greenColor = map(greenfrequency, 19, 250, 255, 0);

  delay(100);

  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  bluefrequency = pulseIn(sOut, LOW);
  blueColor = map(bluefrequency, 7, 144, 255, 0);
  
  delay(100);

  if(redColor > greenColor && redColor > blueColor){
     color = 'R';
     Serial.println("RED");
  }
  else if(greenColor > redColor && greenColor > blueColor){
    color = 'G';
    Serial.println("GREEN");
  }
  else if(blueColor > redColor && blueColor > greenColor){
    color = 'B';
    Serial.println("BLUE");
  }
}

void recieveColors()
{
    
}

void checkColor(char c)
{
  
}

