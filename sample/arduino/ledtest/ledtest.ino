#define LEDPIN 8

void setup() {
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
 digitalWrite(LEDPIN, HIGH);
 delay(500);  // 0.5sec
 digitalWrite(LEDPIN, LOW);
 delay(500);
}
