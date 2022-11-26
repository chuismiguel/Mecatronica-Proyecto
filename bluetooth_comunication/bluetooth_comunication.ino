#include <SoftwareSerial.h>
#include <ArduinoBlue.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

const motor_normalitation_factor = 255/50
int motor_1_speed = 0;
int motor_2_speed = 0;

// Pines
const int BLUETOOTH_TX = 4; //pines del modulo bluetooth
const int BLUETOOTH_RX = 2;

const int pin_motor_1 = 9; //pwn
const int pin_motor_2 = 7; //pwn
const int pin_servo = 11;  //pwn

// Constantes
const int freq = 466;
const int duracion = 500;

int start_time = 0
int actual_time = 0

// Variables
int valorPulsador = 0;
int brillo = 128; 
int valorDesplazamiento, idBoton, idDesplazador;

// Inicializaciones
SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);

ArduinoBlue phone(bluetooth); //creamos el objeto de la libreria ArduinoBlue
Servo servo;  

void setup() {
    // Monitor seria a 9600 bps.
    Serial.begin(9600);

    // Iniciamos bluetooth a 9600 bps
    bluetooth.begin(9600);

    // Una pausa para dejar tiempo a la inicialización
    delay(100);

    // Enviamos comando para renombrar el dispositivo
    bluetooth.write("AT+ScorpioniArduino");

    pinMode(pin_motor_1, OUTPUT);
    pinMode(pin_motor_2, OUTPUT);
    servo.attach(pin_servo); 
}

void loop() {
    // Si se ha pulsado algún botón en el móvil, obtenemos su id
    start_time = millis();
    idBoton = telefono.getButton();
    if (idBoton == 1) {
        myservo.write(180);
        start_time = millis();
    }
    else{
      actual_time = millis();
      // según el botón pulsado hacemos una cosa u otra
      if (actual_time - start_time > 500){
          myservo.write(0);         
        }
    }
    throttle = phone.getThrottle(); //Throttle and steering values go from 0 to 99. when values are at 99/2 = 49, the joystick is at center
    if (throttle > 49) {
      //pwn_value = motor_normalitation_factor * throttle
      motorSpeedA = map(throttle, 49, 99, 0, 255);
      motorSpeedB = map(throttle, 49, 99, 0, 255); 
    }
    else if (throttle < 49){
      motorSpeedA = map(throttle, 0, 49, 0, -255);
      motorSpeedB = map(throttle, 0, 49, 0, -255);  
    }
    else if (throttle == 59){
      motorSpeedA = 0;
      motorSpeedB = 0;    
    }
    
    steering = phone.getSteering(); // Y su valor (va de 0 a 200)
    if (steering > 49) {
     int xMapped = map(steering, 49, 99, 0, 255);
      // Move to left - decrease left motor speed, increase right motor speed
      motorSpeedA = motorSpeedA + xMapped;
      motorSpeedB = motorSpeedB - xMapped;
            
    }
    else if (steering < 49){
     int xMapped = map(steering, 0, 49, 0, 255);
      motorSpeedA = motorSpeedA - xMapped;
      motorSpeedB = motorSpeedB + xMapped;
      
    }
    else if (steering == 49){
      motorSpeedA = 0;
      motorSpeedB = 0;          
  }
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  if (motorSpeedA < 70) {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 70) {
    motorSpeedB = 0;
  }
  
  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
}
