#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
     
// для хранения частоты, считанной фотодиодами
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
     
// для хранения данных о красном, зеленом и синем цветах
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

// подключение к контактам rgb-светодиода
const byte rPin = 9;
const byte gPin = 10;
const byte bPin = 11;
     
void setup() {
      pinMode(S0, OUTPUT);
      pinMode(S1, OUTPUT);
      pinMode(S2, OUTPUT);
      pinMode(S3, OUTPUT);
      //pinMode(rPin, OUTPUT);
      //pinMode(gPin, OUTPUT);
      //pinMode(bPin, OUTPUT);
     
      pinMode(sensorOut, INPUT);
     
      digitalWrite(S0,HIGH);
      digitalWrite(S1,LOW);
     
      Serial.begin(9600);
}
     
void loop() {
      // считывание данных с фотодиодов с красным фильтром
      digitalWrite(S2,LOW);
      digitalWrite(S3,LOW);
     
      redFrequency = pulseIn(sensorOut, LOW);   // считываем выходную частоту
      redColor = map(redFrequency, 70, 120, 255,0);
     
      Serial.print("R = ");
      Serial.print(redColor);
      delay(100);
     
      // считывание данных с фотодиодов с зеленым фильтром
      digitalWrite(S2,HIGH);
      digitalWrite(S3,HIGH);
    
      greenFrequency = pulseIn(sensorOut, LOW); // считываем выходную частоту
      greenColor = map(greenFrequency, 100, 199, 255, 0);
     
      Serial.print(" G = ");
      Serial.print(greenColor);
      delay(100);
     
      // считывание данных с фотодиодов с синим фильтром
      digitalWrite(S2,LOW);
      digitalWrite(S3,HIGH);
     
      blueFrequency = pulseIn(sensorOut, LOW);  // считываем выходную частоту
      blueColor = map(blueFrequency, 38, 84, 255, 0);
     
      Serial.print(" B = ");
      Serial.print(blueColor);
      delay(100);
}
