
const unsigned int IN1_A = 3;
const unsigned int IN2_A = 4;

const unsigned int IN1_B = 5;
const unsigned int IN2_B = 6;
void setup() {
  pinMode(IN1_A, OUTPUT);
  pinMode(IN2_A, OUTPUT);
  pinMode(IN1_B, OUTPUT);
  pinMode(IN2_B, OUTPUT);

} 

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

void loop() {
  motors_bwd();

}
