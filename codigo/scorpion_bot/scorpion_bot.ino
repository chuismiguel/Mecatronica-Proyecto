
#include <SoftwareSerial.h>

const int HIT_REBOUND = 1000; 

const unsigned int RIGHT_SENSOR_PIN = 2;
const unsigned int LEFT_SENSOR_PIN = 3;

const unsigned int IN1_A = 4;
const unsigned int IN2_A = 5;

const unsigned int IN1_B = 6;
const unsigned int IN2_B = 7;

const unsigned int WEAPON = 8;

int last_hit_t = 0;
char val;
int health;

int dmg_flag;
int stopped_t;

SoftwareSerial bt_serial(10,11);

void motors_fwd() {
  digitalWrite(IN1_A , HIGH);
  digitalWrite(IN2_A , LOW); 
  digitalWrite(IN1_B , HIGH); 
  digitalWrite(IN2_B , LOW);
}

void motors_bwd() {
  digitalWrite(IN1_A , LOW);
  digitalWrite(IN2_A , HIGH); 
  digitalWrite(IN1_B , LOW); 
  digitalWrite(IN2_B , HIGH);
}

void motors_left() {
  digitalWrite(IN1_A , LOW);
  digitalWrite(IN2_A , HIGH); 
  digitalWrite(IN1_B , HIGH); 
  digitalWrite(IN2_B , LOW);
}

void motors_right() {
  digitalWrite(IN1_A , HIGH);
  digitalWrite(IN2_A , LOW); 
  digitalWrite(IN1_B , LOW); 
  digitalWrite(IN2_B , HIGH);
}

void motors_stop() {
  digitalWrite(IN1_A , LOW);
  digitalWrite(IN2_A , LOW); 
  digitalWrite(IN1_B , LOW); 
  digitalWrite(IN2_B , LOW);
  digitalWrite(WEAPON , LOW);
}


void hit_weapon() {                          
  digitalWrite(WEAPON , HIGH);
}

void drive_motors() {
  if(bt_serial.available()) {
    val = bt_serial.read();
  }

  if (val == '0') {
    motors_fwd();
    dmg_flag = 1;
  }
  if (val == '1') {
    motors_bwd();
    dmg_flag = 1;
  }
  if (val == '2') {
    motors_left();
    dmg_flag = 1;
  }
  if (val == '3') {
    motors_right();
    dmg_flag = 1;
  }
  if (val == '4') {
    hit_weapon();
    dmg_flag = 0;
    stopped_t = millis();
  }
  if (val == '5') {
    motors_stop();
    dmg_flag = 0;
    stopped_t = millis();
      
  }
}

void detect_dmg() {
  if ((dmg_flag == 0) && (millis - stopped_t > 250)){
    health--;
    bt_serial.write(health);
    Serial.println(health);
  }
}

void setup() {
  pinMode(IN1_A, OUTPUT);
  pinMode(IN2_A, OUTPUT);
  pinMode(IN1_B, OUTPUT);
  pinMode(IN2_B, OUTPUT);
  pinMode(WEAPON, OUTPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT_PULLUP);
  pinMode(LEFT_SENSOR_PIN, INPUT_PULLUP);
  pinMode(WEAPON, OUTPUT);

  health = 100;

  bt_serial.begin(9600);

  Serial.begin(9600); Serial.flush(); while(Serial.available()>0)Serial.read();
  
  attachInterrupt(digitalPinToInterrupt(RIGHT_SENSOR_PIN), detect_dmg, FALLING); // when starting, the alarm is on so we initialize the IR and the button to change alarm mode.
  attachInterrupt(digitalPinToInterrupt(LEFT_SENSOR_PIN), detect_dmg, FALLING);

  dmg_flag = 0;
} 

void loop() {
  drive_motors();
}
