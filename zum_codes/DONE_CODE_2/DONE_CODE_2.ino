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

Servo disk;
Servo tolk;

int container = 0;

class Color
{
  private:
    char color;
    char scan() 
    {
      delay(100);

      int freqs[3] {};
      digitalWrite(s2, LOW);
      digitalWrite(s3, LOW);
      freqs[0] = pulseIn(sOut, LOW, 1000000);
      digitalWrite(s3, HIGH);
      freqs[1] = pulseIn(sOut, LOW, 1000000);
      digitalWrite(s2, HIGH);
      freqs[2] = pulseIn(sOut, LOW, 1000000);
    
      if(freqs[0] > 4 && freqs[0] < 8 && freqs[1] > 13 && freqs[1] < 17 && freqs[2] > 6 && freqs[2] < 11) return 'Y';
      if(freqs[0] > 7 && freqs[0] < 11) return 'R';
      if(freqs[1] > 7 && freqs[1] < 11) return 'B';
      if(freqs[2] > 14 && freqs[2] < 18) return 'G';
      return '0';
    }
  public:
    Color() {this->color = scan();}
    char get_color() {return this->color;}
};
class Packet
{
  private:
    char packet[6];
  public:
    Packet() {
      if (Serial.available() >= 6)
        for (int i = 0; i < 6; i++) 
          this->packet[i] = Serial.read();
      else packet[0] = '0';
    }
    char* get_packet() {return this->packet;}
};
class Container
{
  private:
    char colors[2];
  public:
    Container(char packet[], int number) {
      if (packet[0] == '1' && packet[3] == '2') {
        if (number == 1) {
          this->colors[0] = packet[0];
          this->colors[1] = packet[1];
        }
        else {
          this->colors[0] = packet[4];
          this->colors[1] = packet[5];
        }
      }
    }
    int check_colors(char color){
      if (this->colors[0] == color || this->colors[1] == color) return 1;
      return 0;
    }
};

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

void move_to_container(int cont1, int cont2)
{
  if (cont1 == 1) 
    to_container_N1();

  if (cont2 == 1) 
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
  Packet packet;
  Color cube_color;
  Container container1(packet.get_packet(), 1);
  Container container2(packet.get_packet(), 2);
  //actuate
  move_to_container(container1.check_colors(cube_color.get_color()), container2.check_colors(cube_color.get_color()));  
}
