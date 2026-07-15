const int PULSE_PIN = A0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int pulse = analogRead(PULSE_PIN);
  Serial.println(pulse);
  delay(10);
}
