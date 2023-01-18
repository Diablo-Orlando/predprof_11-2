#define s0 0
#define s1 1
#define s2 2
#define s3 3
#define sOut 4

int redfrequency = 0;
int bluefrequency = 0;
int greenfrequency = 0;

int redColor = 0;
int greenColor = 0;
int blueColor = 0;

int r = 0;
int g = 0;
int b = 0;

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
}

void checkData(char data)
{  
    switch(data){
      case '1': 
      scan();
      break;
      
      default: 
      Serial.println("ERROR");
        }
  }

void scan()
{
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  redfrequency = pulseIn(sOut, LOW);
  redColor = map(redfrequency, 2, 283, 255, 0);
  delay(100);
  
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  bluefrequency = pulseIn(sOut, LOW);
  blueColor = map(bluefrequency, 6, 65, 255, 0);
  delay(100);
  
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  greenfrequency = pulseIn(sOut, LOW);
  greenColor = map(greenfrequency, 12, 78, 255, 0);
  delay(100);
  
  if(redColor > greenColor && redColor > blueColor){
     Serial.println("RED");
  }
  if(greenColor > redColor && greenColor > blueColor){
    Serial.println("GREEN");
  }
  if(blueColor > redColor && blueColor > greenColor){
    Serial.println("BLUE");
  }
}
