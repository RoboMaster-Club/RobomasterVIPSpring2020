void setup() {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(3, HIGH);
}

void loop() {
  delay(1000);
  digitalWrite(6, HIGH);
  digitalWrite(5, LOW);
  delay(1000);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
 }
