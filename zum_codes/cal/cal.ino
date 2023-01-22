// Пины подключения
#define pinS0 8
#define pinS1 9
#define pinS2 10
#define pinS3 11
#define pinOut 12
int freq=0;

void setup() {
  // сконфигурировать пины
  pinMode(pinS0, 1);
  pinMode(pinS1, 1);
  pinMode(pinS2, 1);
  pinMode(pinS3, 1);
  pinMode(pinOut, 0);

  // масштабирование 20%
  digitalWrite(pinS0,1);
  digitalWrite(pinS1,0);

  Serial.begin(9600);
}
void loop() {
  // установить R фильтр
  digitalWrite(pinS2,0);
  digitalWrite(pinS3,0);
  // Получение частоты на выходе
  freq = pulseIn(pinOut, 0);
  // вывод в последовательный порт
  Serial.print("R= ");
  Serial.print(freq);
  delay(150);
  // установить G фильтр
  digitalWrite(pinS2,1);
  digitalWrite(pinS3,1);
  // Получение частоты на выходе
  freq = pulseIn(pinOut, 0);
  // вывод в последовательный порт
  Serial.print(" G= ");
  Serial.print(freq);
  delay(150);
  // установить B фильтр
  digitalWrite(pinS2,0);
  digitalWrite(pinS3,1);
  // Получение частоты на выходе
  freq = pulseIn(pinOut, 0);
  // вывод в последовательный порт
  Serial.print(" B= ");
  Serial.println(freq);
  delay(150);
}
