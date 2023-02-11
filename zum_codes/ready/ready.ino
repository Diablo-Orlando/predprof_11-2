 #include <Servo.h>

#define DISK_PIN 6
#define TOLKATEL_PIN 5
#define OE 13
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
<<<<<<< HEAD
int moving();
=======
int scanRED();
int scanBLUE();
int scanGREEN();
int moving();
void writeColors(char colors[]);
void amountColors(char colors[]);
>>>>>>> 2d638f55faf19c151addc11b8d9ec234483dff82

char stat = 'S';

char container_1_colors[2] {};
char container_2_colors[2] {};
int amount = 0;

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
  
  digitalWrite(OE, LOW);
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
<<<<<<< HEAD
 if (Serial.available() >= 6) { 
    if (checkData() != '0') {
=======
  if (Serial.available() >= 6) { 
    if (checkData() != '0')
>>>>>>> 2d638f55faf19c151addc11b8d9ec234483dff82
      Serial.println(container_1_colors[0]);
      Serial.println(container_1_colors[1]);
      Serial.println(container_2_colors[0]);
      Serial.println(container_2_colors[1]);
<<<<<<< HEAD
      if (moving() != 0) {
        Serial.println("Working");
        }
    }
=======
      Serial.write(container_1_colors[0]);
      moving();
>>>>>>> 2d638f55faf19c151addc11b8d9ec234483dff82
  }
  
}

void amountColors(char colors[])
{
  for (int i = 0; i < 6; i++)
    if (colors[i] != '0')
      amount++;
}

void writeColors(char colors[])
{
  container_1_colors[0] = colors[1];
  container_1_colors[1] = colors[2];
  container_2_colors[0] = colors[4];
  container_2_colors[1] = colors[5];
}

void writeColors(char colors[])
{
  container_1_colors[0] = colors[1];
  container_1_colors[1] = colors[2];
  container_2_colors[0] = colors[4];
  container_2_colors[1] = colors[5];
}

char checkData()
{
<<<<<<< HEAD
  char recievedData[6];
  for (int i = 0; i < 6; i++)
    recievedData[i] = Serial.read();
  if (recievedData[0] == '1' && recievedData[3] == '2')
    writeColors(recievedData);
  else if (recievedData[0] == 'E') digitalWrite(OE, LOW);
  else if (recievedData[0] == 'D') digitalWrite(OE, HIGH);
=======
  char recievedData[6] {};
  for (int i = 0; i < 6; i++)
    recievedData[i] = Serial.read();
  if (recievedData[0] == '1' && recievedData[3] == '2') {
    writeColors(recievedData);
    amountColors(recievedData);
    Serial.flush();
  }
>>>>>>> 2d638f55faf19c151addc11b8d9ec234483dff82
  else return '0';
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
  digitalWrite(OE, LOW);
  delay(100);

  int frequency = scanRED();
  if(frequency > 11 && frequency < 23) {
    digitalWrite(OE, HIGH);
    return 'R';
  }
  
  frequency = scanBLUE();
  if(frequency > 5 && frequency < 16) {
    digitalWrite(OE, HIGH);
    return 'B';
  }
  
  frequency = scanGREEN();
  if(frequency > 16 && frequency < 55) {
    digitalWrite(OE, HIGH);
    return 'G';
<<<<<<< HEAD

   return '0';
=======
  }

  int* freqs = scanYELLOW();
  if(freqs[0] > 6 && freqs[0] < 10 && freqs[1] > 19 && freqs[1] < 25 && freqs[2] < 8 && freqs[2] > 15) {
    digitalWrite(s0, LOW);
    digitalWrite(OE, HIGH);
    return 'Y';
  }

  return '0';
>>>>>>> 2d638f55faf19c151addc11b8d9ec234483dff82
}

int moving()
{
  if (stat != 'W') {
    stat = 'W';
    char color = scan();
<<<<<<< HEAD
    if (color != 0){
      for (int i = 0; i < 2; i++) {
        if (container_1_colors[i] == color) {
          to_container_N1();
          }
        else if (container_2_colors[i] == color) {
          to_container_N2();
          }
        else return 0;
        }
    }
  }
    else return 0;
=======
    for (int i = 0; i < amount; i ++) {
      for (int j = 0; j < 2; j++) {
        if (container_1_colors[j] == color) {
          container_1_colors[j] = 0;
          to_container_N1();
          }
        else if (container_2_colors[j] == color) {
          container_2_colors[j] = 0;
          to_container_N2();
          }
        else return 0;
      }
    }
    Serial.println("done");
  }
  return 1;
>>>>>>> 2d638f55faf19c151addc11b8d9ec234483dff82
}
