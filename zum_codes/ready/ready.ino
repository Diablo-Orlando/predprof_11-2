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

char checkData();
void to_start(Servo serv);
void to_container_N1();
void to_container_N2();
void tolkatel();
char scan();
void moving();

char container_1_colors[2] {};
char container_2_colors[2] {};

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
    char color = checkData();
  }
}

char checkData()
{
  char recievedData = Serial.read();
  return recievedData;
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

int scanRED()
{
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  int freq = pulseIn(sOut, LOW, 1000000);
  return freq;
}

int scanBLUE()
{
  digitalWrite(s3, HIGH);
  int freq = pulseIn(sOut, LOW, 1000000);
  return freq;
}

int scanGREEN()
{
  digitalWrite(s2, HIGH);
  int freq = pulseIn(sOut, LOW, 1000000);
  return freq;
}

char scan()
{
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);

  int frequency = scanRED();
  if(frequency > 4 && frequency < 23)
    return 'R';
  
  frequency = scanBLUE();
  if(frequency > 5 && frequency < 16)
    return 'B';
  
  frequency = scanGREEN();
  if(frequency > 16 && frequency < 55)
    return 'G';
}

void moving()
{
  char color = scan();
  
}
