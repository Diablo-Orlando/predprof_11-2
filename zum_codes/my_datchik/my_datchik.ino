#define s0 8
#define s1 9
#define s2 10
#define s3 11
#define sOut 12

int redfrequency = 0;
int bluefrequency = 0;
int greenfrequency = 0;

int redColor = 0;
int greenColor = 0;
int blueColor = 0;

void checkData(char data);
void scan();

void setup() {
   pinMode(s0, OUTPUT);
   pinMode(s1, OUTPUT);
   pinMode(s2, OUTPUT);
   pinMode(s3, OUTPUT);

   pinMode(sOut, INPUT);

   digitalWrite(s0, HIGH);
   digitalWrite(s1, LOW);

  Serial.begin(9600);
}

void loop() {
  scan();
//  if (Serial.available() > 0) { 
//    char dataBuffer = Serial.read();
//    checkData(dataBuffer);
//    }
}

void checkData(char data) {  
    switch(data){
      case 'S':
      scan();
      default: 
          Serial.println("ERROR");
          break;
        }
}

void scan()
{
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  redfrequency = pulseIn(sOut, LOW);
  redColor = map(redfrequency, 162, 148, 255, 0);
  delay(100);

  digitalWrite(s3, HIGH);
  bluefrequency = pulseIn(sOut, LOW);
  blueColor = map(bluefrequency, 126, 137, 255, 0);
  delay(100);
  
  digitalWrite(s2, HIGH);
  greenfrequency = pulseIn(sOut, LOW);
  greenColor = map(greenfrequency, 182, 206, 255, 0);
  delay(100);

  if(redfrequency > 4 && redfrequency < 23)
    Serial.println("RED");
  else if(greenfrequency > 15 && greenfrequency < 55)
    Serial.println("GREEN");
  else if(bluefrequency > 5 && bluefrequency < 12)
    Serial.println("BLUE");
  else 
    Serial.println("NO OBJECT");

//  if(redColor > greenColor && redColor > blueColor){
//    Serial.println("RED");
//  }
//  else if(greenColor > redColor && greenColor > blueColor){
//    Serial.println("GREEN");
//  }
//  else if(blueColor > redColor && blueColor > greenColor){
//    Serial.println("BLUE");
//  }
}
