#include <Servo.h>

#define DISK_PIN 6
#define TOLKATEL_PIN 5
#define led 13
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

char container_1_colors[2] {};
char container_2_colors[2] {};
char packet[6] {};
char cube_color;
int container = 0;

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
  
  digitalWrite(led, HIGH);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);

  disk.attach(DISK_PIN);
  tolk.attach(TOLKATEL_PIN);
  
  to_start(disk);
  to_start(tolk);
}

void check_packet()
{
  if (Serial.available() >= 6)
    for (int i = 0; i < 6; i++) 
      packet[i] = Serial.read();
  return;
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

int *scanYELLOW()
{
  static int freqs[3] {};
  freqs[0] = scanRED();
  freqs[1] = scanBLUE();
  freqs[2] = scanGREEN();
  return freqs;
}

char scan()
{
  delay(100);

  int* freqs = scanYELLOW();
  if(freqs[0] > 6 && freqs[0] < 11 && freqs[1] > 13 && freqs[1] < 22 && freqs[2] > 8 && freqs[2] < 15) {
    return 'Y';
  }

  int frequency = scanRED();
  if(frequency > 8 && frequency < 12) {
    return 'R';
  }
  
  frequency = scanBLUE();
  if(frequency > 8 && frequency < 12) {
    return 'B';
  }
  
  frequency = scanGREEN();
  if(frequency > 14 && frequency < 21) {
    return 'G';
  }
  
  return '0';
}

void setup_container(char _packet[])
{
  if ( _packet[0] == '1' && _packet[3] == '2') {
    container_1_colors[0] = _packet[1];
    container_1_colors[1] = _packet[2];
    container_2_colors[0] = _packet[4];
    container_2_colors[1] = _packet[5];
    packet[0] = "-1";
  }
  else Serial.println("packet ignored");
  return;
}

int set_container(char color)
{
  if (color == container_1_colors[0] || color == container_1_colors[1]) return 1;
  else if (color == container_2_colors[0] || color == container_2_colors[1]) return 2;
  return 0;
}

void move_to_container(int _container)
{
  if (_container == 0) return;

  if (_container == 1) 
    to_container_N1();

  if (_container == 2) 
    to_container_N2();

  return;
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

void loop() 
{
  //update
  check_packet();
  cube_color = scan();
  //model
  setup_container(packet);
  container = set_container(cube_color);
  //actuate
  move_to_container(container);  
}
