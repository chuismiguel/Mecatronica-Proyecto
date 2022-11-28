int RIGHT_SENSOR_PIN = 2;
int LEFT_SENSOR_PIN = 3;

int hit_cts = 0;
void setup() {
  pinMode(LEFT_SENSOR_PIN, INPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
 if ((digitalRead(LEFT_SENSOR_PIN) == 1) || (digitalRead(RIGHT_SENSOR_PIN))){
   hit_cts++;
   Serial.println("HIT");
   Serial.println(hit_cts);

 }
}
