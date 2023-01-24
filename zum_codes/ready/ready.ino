#include <Servo.h>

#define DISK_PIN 6
#define TOLKATEL_PIN 5
#define s0 12
#define s1 11
#define s2 10
#define s3 9
#define sOut 8

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
char scan();
void checkColor(char c);
void moving();

char container_1_colors[2] {};
char container_2_colors[2] {};

int redfrequency = 0;
int bluefrequency = 0;
int greenfrequency = 0;

void setup() 
{
  Serial.begin(BQ_BLUETOOTH);

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(DISK_PIN, OUTPUT);
  pinMode(TOLKATEL_PIN, OUTPUT);

  pinMode(sOut, INPUT);

  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);

  disk.attach(DISK_PIN);
  tolk.attach(TOLKATEL_PIN);
  
  to_start(disk);
  to_start(tolk);
}

void debug()
{
  for (int i = 0; i < 2; i++)
    Serial.println(container_1_colors[i]);
  }


void loop() 
{
 if (Serial.available() > 0) { 
    checkData();
  }
}

void checkData()
{
  if (Serial.read() == 'C') {
    for (int i = 0; i < 2; i++){
       container_1_colors[i] = Serial.read();
    }
    for(int i = 0; i < 2; i++) {
       container_2_colors[i] = Serial.read();
    }
  }
  else if (Serial.read() == 'I') {
      debug();
      moving();
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

char scan()
{
   digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  redfrequency = pulseIn(sOut, LOW);
  if(redfrequency > 4 && redfrequency < 23) {
    Serial.println("RED");
    return 'R';
  }
  delay(100);

  digitalWrite(s3, HIGH);
  bluefrequency = pulseIn(sOut, LOW);
  if(bluefrequency > 5 && bluefrequency < 16) {
    Serial.println("BLUE");
    return 'B';
  }
  delay(100);
  
  digitalWrite(s2, HIGH);
  greenfrequency = pulseIn(sOut, LOW);
  if(greenfrequency > 16 && greenfrequency < 55) {
    Serial.println("GREEN");
    return 'G';
  }
  delay(100);
}

void moving()
{
  char color = scan();
  for (int i = 0; i < 2; i++) {
    if (color == container_1_colors[i]) {
      container_1_colors[i] = '0';
      to_container_N1();
      }
    else if (color == container_2_colors[i]) {
      container_2_colors[i] = '0';
      to_container_N2();
      }
    } 
}
