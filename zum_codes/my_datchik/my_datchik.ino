#define s0 4
#define s1 3
#define s2 2
#define s3 1
#define sOut 0

int redfrequency = 0;
int bluefrequency = 0;
int greenfrequency = 0;

int rm = 0;
int gm = 0;
int bm = 0;

int r = 1000;
int g = 1000;
int b = 1000;

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
//      default: 
//          Serial.println("ERROR");
//          break;
        }
}

void scan()
{
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  redfrequency = pulseIn(sOut, LOW);
  redColor = map(redfrequency, 162, 148, 255, 0);

//  Serial.print("R = ");
//  Serial.println(redfrequency);
//  if (redfrequency > rm)
//    rm = redfrequency;
//  if (redfrequency < r)
//    r = redfrequency;
//  Serial.print("rmax = ");
//  Serial.println(rm);
//  Serial.print("rmin = ");
//  Serial.println(r);
  
  delay(100);
  
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  greenfrequency = pulseIn(sOut, LOW);
  greenColor = map(greenfrequency, 182, 206, 255, 0);


//  Serial.print("B = ");
//  Serial.println(bluefrequency);
//  if (bluefrequency > bm)
//    bm = bluefrequency;
//  if (bluefrequency < b)
//    b = bluefrequency;
//  Serial.print("bmax = ");
//  Serial.println(bm);
//  Serial.print("bmin = ");
//  Serial.println(b);

  delay(100);

  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  bluefrequency = pulseIn(sOut, LOW);
  blueColor = map(bluefrequency, 126, 137, 255, 0);
  
  
//  Serial.print("G = ");
//  Serial.println(greenfrequency);
//  if (greenfrequency > gm)
//    gm = greenfrequency;
//  if (greenfrequency < g)
//    g = greenfrequency;
//  Serial.print("gmax = ");
//  Serial.println(gm);
//  Serial.print("gmin = ");
//  Serial.println(g);
  
  delay(100);
  
  if(redColor > greenColor && redColor > blueColor){
     Serial.println("RED");
  }
  else if(greenColor > redColor && greenColor > blueColor){
    Serial.println("GREEN");
  }
  else if(blueColor > redColor && blueColor > greenColor){
    Serial.println("BLUE");
  }

//  if(redfrequency > 148 && redfrequency < 162 && greenfrequency > 212 && greenfrequency < 239 && bluefrequency > 141 && bluefrequency < 163){
//     Serial.println("RED");
//  }
//  else if(redfrequency > 153 && redfrequency < 169 && greenfrequency > 182 && greenfrequency < 206 && bluefrequency > 150 && bluefrequency < 170){
//    Serial.println("GREEN");
//  }
//  else if(redfrequency > 126 && redfrequency < 139 && greenfrequency > 211 && greenfrequency < 226 && bluefrequency > 126 && bluefrequency < 137){
//    Serial.println("BLUE");
//  }
}
