#define LED 32

void setup() {
  //Serial.begin(115200);
  //Serial.println("Hello, ESP32!");
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}
