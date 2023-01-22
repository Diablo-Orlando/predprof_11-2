const int s0 = 7;
const int s1 = 6;
const int s2 = 5;
const int s3 = 4;
const int out = 3;
// Variables
int red = 0;
int green = 0;
int blue = 0;

// Calibrated value
int cal_min = 5;
int cal_max_r = 50;
int cal_max_g = 50;
int cal_max_b = 50;

void calibrate() {
  Serial.println("Clear sensor area. Then enter r again");
    while (Serial.read() != 'r') {
      //do nothing
      ;
    }
    color();
    cal_max_r = red;
    cal_max_g = green;
    cal_max_b = blue;
    Serial.println("Put white color infront of sensor, Then enter r again");
    while (Serial.read() != 'r') {
      //do nothing
      ;
    }
    color();
    cal_min = (red + green + blue) / 3;
    Serial.println("calibrated successfully.");
    delay(300);
}

void color() {
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  //count OUT, pRed, RED
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  //count OUT, pBLUE, BLUE
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  //count OUT, pGreen, GREEN
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}

void cheto()
{
  red = map(red, cal_min, cal_max_r, 255, 0);
  green = map(green, cal_min, cal_max_g, 255, 0);
  blue = map(blue, cal_min, cal_max_b, 255, 0);
  Serial.print("R Intensity:");
  Serial.print(red);
  Serial.print(" G Intensity: ");
  Serial.print(green);
  Serial.print(" B Intensity : ");
  Serial.println(blue);
  delay(200);
 }

void setup()
{
  Serial.begin(9600);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
}

void loop()
{
  if (Serial.read() == 'r') {
    calibrate();
  }

  else if (Serial.read()== 'h') {
    cheto();
  }

  
}
