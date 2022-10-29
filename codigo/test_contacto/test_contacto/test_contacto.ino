int HIT_SENSOR_PIN = 3;
int LED_BOARD = 13;

void setup() {
  pinMode(LED_BOARD, OUTPUT);
  pinMode(HIT_SENSOR_PIN, INPUT);

}

void loop() {
 digitalWrite(LED_BOARD, digitalRead(HIT_SENSOR_PIN));
}
